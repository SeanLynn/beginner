using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Collections;

namespace SYKScenic
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    /// 

    public partial class MainWindow : Window
    {

        private string listboxAddEllipse = "listboxAddEllipse";
        private Ellipse newEllipse; //新生成的Ellipse
        private Point targetPoint;  //当前鼠标点击的点
        private Ellipse targetEllipse; //可移动的Ellipse，鼠标点击的Ellipse
        private Ellipse startEllipse; //连线用的起始点
        private Ellipse endEllipse;
        private Path newPath;
        private Dictionary<string, Vertex> VertexAdj = new Dictionary<string, Vertex>();
        private ParkingLot parkingLot;
        private static int stackSize = 5;
        private Stack<Car> carStack = new Stack<Car>(stackSize);
        private Queue<Car> carQueue = new Queue<Car>();
        //private Stack<Car> carStack = new Stack<Car>();
        private ArrayList InfoElements = new ArrayList();
        private ArrayList PathList = new ArrayList();
        private ArrayList MovePathListStartP = new ArrayList();
        private ArrayList MovePathListEndP = new ArrayList();
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, RoutedEventArgs e)
        {
            var app = Application.Current;

            InfoElements.Add(VEAdjustGrid);

        }

        private void Canvas_MouseLeftDown(object sender, MouseButtonEventArgs e)
        {
            //确保ListBox消失
            var listbox = (UIElement)LogicalTreeHelper.FindLogicalNode(LTLCanvas, listboxAddEllipse);
            if (listbox != null)
            {
                LTLCanvas.Children.Remove(listbox);
            }

            //移动Ellipse坐的准备
            targetEllipse = Mouse.DirectlyOver as Ellipse;
            if (targetEllipse != null)
            {
                targetPoint = e.GetPosition(targetEllipse);
                if (VertexAdj.ContainsKey(targetEllipse.Name))
                {
                    //没有选终点提示文字并且起点为空
                    if (LinePrompt.Visibility != Visibility.Hidden && startEllipse != null)
                    {
                        //划线
                        var pCanvas = e.GetPosition(LTLCanvas);
                        LineGeometry myLineGeometry = new LineGeometry();
                        Point startPoint = new Point(Canvas.GetLeft(startEllipse) + 35, Canvas.GetTop(startEllipse) + 35);
                        Point endPoint = new Point(pCanvas.X - targetPoint.X + 35, pCanvas.Y - targetPoint.Y + 35);
                        myLineGeometry.StartPoint = startPoint;
                        myLineGeometry.EndPoint = endPoint;
                        Path myPath = new Path();
                        myPath.Stroke = Brushes.Black;
                        myPath.StrokeThickness = 1;
                        myPath.Data = myLineGeometry;

                        //设置线的显示程度
                        Canvas.SetZIndex(myPath, 1);
                        Canvas.SetZIndex(startEllipse, 2);
                        Canvas.SetZIndex(targetEllipse, 2);

                        //如果以前画了线但是没有保存就把它清除
                        if (newPath != null)
                        {
                            PathList.Remove(newPath);
                            LTLCanvas.Children.Remove(newPath);
                        }

                        newPath = myPath;
                        LTLCanvas.Children.Add(myPath);
                        PathList.Add(myPath);
                        LinePrompt.Visibility = Visibility.Hidden;
                        endEllipse = targetEllipse;
                    }
                    //更新节点信息
                    Vertex vertex = VertexAdj[targetEllipse.Name];
                    VertexName.Text = vertex.name.Substring(1, vertex.name.Length - 1);
                    VertexName.IsEnabled = false; //已经存在的点的名字不允许改变
                    VertexPopularityTextBox.Text = (vertex.popularity).ToString();
                    VertexInfo.Text = vertex.info;
                    if (vertex.restArea)
                    {
                        HasRestArea.IsChecked = true;
                    }
                    else
                    {
                        HasRestArea.IsChecked = false;
                    }
                    if (vertex.WC)
                    {
                        HasWC.IsChecked = true;
                    }
                    else
                    {
                        HasWC.IsChecked = false;
                    }
                    //更新相关Path信息
                    var Pcanvas = e.GetPosition(LTLCanvas);
                    Point PathSEPoint = targetPoint;
                    PathSEPoint.X = Pcanvas.X - PathSEPoint.X + 35;
                    PathSEPoint.Y = Pcanvas.Y - PathSEPoint.Y + 35;
                    foreach (Path path in PathList)
                    {
                        LineGeometry geo = path.Data as LineGeometry;

                        if (geo != null && geo.StartPoint == PathSEPoint)
                        {
                            MovePathListStartP.Add(path);
                        }
                        else if (geo != null && geo.EndPoint == PathSEPoint)
                        {
                            MovePathListEndP.Add(path);
                        }
                    }
                    return;
                }
            }

            VertexName.Text = "";
            VertexName.IsEnabled = true;
            VertexPopularityTextBox.Text = "0";
            VertexInfo.Text = "";
            HasRestArea.IsChecked = false;
            HasWC.IsChecked = false;
        }

        private void Canvas_MouseUp(object sender, MouseButtonEventArgs e)
        {
            //鼠标松开后，将选中控件设置成null
            //targetEllipse = null;
            MovePathListStartP.Clear();
            MovePathListEndP.Clear();
        }

        //响应鼠标拖动Ellipse事件
        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            //确定鼠标左键处于按下状态并且有元素被选中
            if (e.LeftButton == MouseButtonState.Pressed && targetEllipse != null)
            {
                var pCanvas = e.GetPosition(LTLCanvas);
                var textbox = (UIElement)LogicalTreeHelper.FindLogicalNode(LTLCanvas, targetEllipse.Name + "TextBlcok");

                //设置最终位置
                Canvas.SetLeft(targetEllipse, pCanvas.X - targetPoint.X);
                Canvas.SetTop(targetEllipse, pCanvas.Y - targetPoint.Y);

                if (textbox != null)
                {
                    Canvas.SetLeft(textbox, pCanvas.X - targetPoint.X + 25);
                    Canvas.SetTop(textbox, pCanvas.Y - targetPoint.Y - 15);
                }

                //设置与点相关的线的运动
                Point point = new Point(pCanvas.X - targetPoint.X + 35, pCanvas.Y - targetPoint.Y + 35);
                foreach (Path path in MovePathListStartP)
                {
                    LineGeometry geo = path.Data as LineGeometry;
                    geo.StartPoint = point;
                }
                foreach (Path path in MovePathListEndP)
                {
                    LineGeometry geo = path.Data as LineGeometry;
                    geo.EndPoint = point;
                }

                PositionX.Text = (pCanvas.X - targetPoint.X).ToString();
                PositionY.Text = (pCanvas.Y - targetPoint.Y).ToString();
            }
        }

        //鼠标右键点击生成Ellipse
        private void Canvas_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {

            var listbox = (UIElement)LogicalTreeHelper.FindLogicalNode(LTLCanvas, listboxAddEllipse);
            if (listbox != null)
            {
                LTLCanvas.Children.Remove(listbox);
            }

            Point pos = e.GetPosition(LTLCanvas);
            //右键选项
            ListBox lb = new ListBox();
            lb.Name = listboxAddEllipse;
            Canvas.SetLeft(lb, pos.X);
            Canvas.SetTop(lb, pos.Y);
            ListBoxItem lbi1 = new ListBoxItem();
            lbi1.Content = "在此处添加景点";
            lbi1.Width = 100;
            lbi1.AddHandler(UIElement.MouseDownEvent,
                new MouseButtonEventHandler(ListBoxItemAddEllipseEventHandler), true);
            lb.Items.Add(lbi1);

            startEllipse = Mouse.DirectlyOver as Ellipse;

            //针对已保存的景点
            if (startEllipse != null && VertexAdj.ContainsKey(startEllipse.Name))
            {
                ListBoxItem lbi2 = new ListBoxItem();
                lbi2.Content = "此点为连线起点";
                lbi2.Width = 100;
                lbi2.AddHandler(UIElement.MouseDownEvent,
                    new MouseButtonEventHandler(ListBoxItemAddLineEventHandler), true);
                lb.Items.Add(lbi2);
            }
            else
            {
                startEllipse = null;
            }
            Canvas.SetZIndex(lb, 1002); //1002是为了让ListBox显示在圆上
            LTLCanvas.Children.Add(lb);
        }

        private void ListBoxItemAddLineEventHandler(object sender, MouseButtonEventArgs e)
        {
            //鼠标右键ListBoxItem点击时间处理
            var listbox = (UIElement)LogicalTreeHelper.FindLogicalNode(LTLCanvas, listboxAddEllipse);
            LTLCanvas.Children.Remove(listbox);
            LinePrompt.Visibility = Visibility.Visible;
        }

        private void ListBoxItemAddEllipseEventHandler(object sender, MouseButtonEventArgs e)
        {
            //鼠标右键ListBoxItem点击时间处理
            var listbox = (UIElement)LogicalTreeHelper.FindLogicalNode(LTLCanvas, listboxAddEllipse);
            Point pos = e.GetPosition(LTLCanvas);
            //以鼠标点击处为圆心画圆
            Ellipse elips = new Ellipse();
            if (newEllipse != null)
            {
                LTLCanvas.Children.Remove(newEllipse);
            }
            newEllipse = elips;
            elips.Stroke = SystemColors.WindowTextBrush;
            elips.Width = 70;
            elips.Height = 70;
            elips.Fill = Brushes.Aquamarine;
            elips.Name = "Null";
            LTLCanvas.Children.Add(elips);
            Canvas.SetLeft(elips, pos.X - 35);
            Canvas.SetTop(elips, pos.Y - 35);

            PositionX.Text = (pos.X - 35).ToString();
            PositionY.Text = (pos.Y - 35).ToString();
            VertexName.Text = "";
            VertexInfo.Text = "";
            VertexPopularityTextBox.Text = "0";
            LTLCanvas.Children.Remove(listbox);
        }

        private void OnTourGraph(object sender, RoutedEventArgs e)
        {

            StringBuilder msg = new StringBuilder(1024);
            Console.WriteLine(ScenicDll.GetTourGuide(msg));
            Information.Text = "导游图为： " + msg.ToString();
        }

        private void OnLoopWay(object sender, RoutedEventArgs e)
        {
            StringBuilder msg = new StringBuilder(1024);
            Console.WriteLine("GetLoopGraph:: " + ScenicDll.GetLoopGraph(msg));
            Information.Text = msg.ToString();
        }

        private void OnMiniDistance(object sender, RoutedEventArgs e)
        {
            if (startVertex.Text == "" || endVertex.Text == "")
            {
                return;
            }
            string start = "_" + startVertex.Text;
            string end = "_" + endVertex.Text;
            StringBuilder msg = new StringBuilder(1024);
            ScenicDll.MiniDistance(msg, start, end);
            Information.Text = msg.ToString();
        }

        private void OnMiniSpanTree(object sender, RoutedEventArgs e)
        {
            StringBuilder msg = new StringBuilder(1024);
            Console.WriteLine("MiniSpanTree::" + ScenicDll.MiniSpanTree(msg));
            Information.Text = msg.ToString();
        }

        private void OnSortByPopularity(object sender, RoutedEventArgs e)
        {
            StringBuilder msg = new StringBuilder(1024);
            Console.WriteLine("OnSortByPopularity::" + ScenicDll.SortByPopularity(msg));
            Information.Text = msg.ToString();
        }

        private void OnKeySearch(object sender, RoutedEventArgs e)
        {
            StringBuilder msg = new StringBuilder(1024);
            msg.Append(keyWord.Text);
            Console.WriteLine("OnSortByPopularity::" + ScenicDll.KeySearch(msg));
            Information.Text = msg.ToString();
        }

        private void OnParkingLot(object sender, RoutedEventArgs e)
        {
            parkingLot = new ParkingLot(carStack, carQueue, stackSize);
            parkingLot.Show();
        }

        //保存边
        private void OnSaveEdge(object sender, RoutedEventArgs e)
        {
            if (startEllipse == endEllipse)
            {
                return;
            }

            //如果起点或终点为空，那么边保存无效
            if (startEllipse == null || endEllipse == null)
            {
                if (newPath != null)
                {
                    PathList.Remove(newPath);
                    LTLCanvas.Children.Remove(newPath);
                }
            }
            else
            {
                string startName = startEllipse.Name;
                string endName = endEllipse.Name;
                //确保边权重是个数
                int distance;
                if (int.TryParse(EdgeDistance.Text, out distance) == false)
                {
                    PromptChange.Visibility = Visibility.Visible;
                    return;
                }

                uint dis = uint.Parse(distance.ToString());

                uint edgesN = ScenicDll.CreateNewEdge(startName, endName, dis);
                Console.WriteLine("edgesN = " + edgesN);
            }
            //将相关引用置空
            startEllipse = null;
            endEllipse = null;
            newPath = null;
            PromptChange.Visibility = Visibility.Hidden;
            EdgeDistance.Text = "0";
        }

        //响应保存按钮
        private void OnVertexSave(object sender, RoutedEventArgs e)
        {
            if (newEllipse == null && targetEllipse == null)
            {
                return;
            }


            if (VertexName.Text.Equals(""))
            {
                return;
            }

            string name = "_" + VertexName.Text;
            int popularity;
            string info = VertexInfo.Text;
            bool restArea = HasRestArea.IsChecked.Value;
            bool WC = HasWC.IsChecked.Value;
            //如果用户输入的内容不符合规制，
            if (int.TryParse(VertexPopularityTextBox.Text, out popularity) == false || name.Equals(""))
            {
                PromptChange.Visibility = Visibility.Visible;
                return;
            }

            uint popu = uint.Parse(popularity.ToString());
            //如果不是新的点
            Console.WriteLine("onsaveVertex");
            if (VertexAdj.ContainsKey(name))
            {
                Vertex v = VertexAdj[name];
                v.reset(popu, info, restArea, WC);
                ScenicDll.CreateNewVertex(name, popu, info, restArea, WC);
                VertexAdj[name] = v;
            }
            else if (newEllipse != null)//如果是新的点
            {
                Vertex v = new Vertex(name, popu, info, restArea, WC);
                v.number = ScenicDll.CreateNewVertex(name, popu, info, restArea, WC);

                VertexAdj.Add(v.name, v);
                //点保存之后，设置点上的景点名称
                TextBlock newTextBlock = new TextBlock();
                newTextBlock.Text = v.name.Substring(1, v.name.Length - 1);
                Canvas.SetTop(newTextBlock, Canvas.GetTop(newEllipse) - 15);
                Canvas.SetLeft(newTextBlock, Canvas.GetLeft(newEllipse) + 25);
                Canvas.SetZIndex(newTextBlock, 1001);
                newTextBlock.Name = v.name + "TextBlcok";
                LTLCanvas.Children.Add(newTextBlock);
                newEllipse.Name = v.name;
                newEllipse = null;
            }
            //添加之后放弃指向
            PromptChange.Visibility = Visibility.Hidden;
            VertexName.Text = "";
            VertexInfo.Text = "";
            VertexPopularityTextBox.Text = "0";
        }
    }
}
