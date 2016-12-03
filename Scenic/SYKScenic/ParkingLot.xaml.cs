using System;
using System.Collections;
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
using System.Windows.Shapes;

namespace SYKScenic
{
    /// <summary>
    /// ParkingLot.xaml 的交互逻辑
    /// </summary>
    public partial class ParkingLot : Window
    {
        private Stack<Car> carStack;
        private Queue<Car> carQueue;
        private int capacity;
        public ParkingLot(Stack<Car> cs, Queue<Car> cq, int c)
        {
            InitializeComponent();
            carStack = cs;
            carQueue = cq;
            capacity = c;
            InitializeStack();
            InitializeQueue();
        }

        private void InitializeStack()
        {
            foreach (Car c in carStack)
            {
                Border myBorder = GetNewBorder(c);
                StackParkingLot.Children.Add(myBorder);
            }
        }

        private void InitializeQueue()
        {
            foreach (Car c in carQueue)
            {
                Border myBorder = GetNewBorder(c);
                QueueParkingLot.Children.Add(myBorder);
            }
        }

        private void OnPushCar(object sender, RoutedEventArgs e)
        {
            if (CarName.Text == "")
            {
                return;
            }

            Car c = new Car(CarName.Text, DateTime.Now);
            StringBuilder builder = new StringBuilder(256);
            pushCar(c, builder);
            ParkingLotInfo.Text = builder.ToString();
            CarName.Text = "";
        }

        private void pushCar(Car c, StringBuilder builder)
        {
            foreach (Car r in carStack)
            {
                if (r.getName() == c.getName())
                {
                    builder.Append("车已经存在停车场。\n");
                    return;
                }
            }

            builder.Append("进场车牌为： " + c.getName() + "\n");
            Border myBorder = GetNewBorder(c);
            if (carStack.Count() < capacity)
            {
                builder.Append("进场时刻为： " + c.getStart().ToString());
                carStack.Push(c);
                builder.Append("\n该车已进入停车场在：" + carStack.Count() + "号车道\n");
                StackParkingLot.Children.Add(myBorder);
            }
            else
            {
                builder.Append("停车场已满，该车停在便道上。\n");
                carQueue.Enqueue(c);
                QueueParkingLot.Children.Add(myBorder);
            }
        }

        private void OnPopCar(object sender, RoutedEventArgs e)
        {
            StringBuilder builder = new StringBuilder(256);
            if (carStack.Count() == 0)
            {
                builder.Append("停车场是空的。\n");
                return;
            }
            string name = CarName.Text;
            if (popCar(name, builder) && carQueue.Count() != 0)
            {
                Car r = carQueue.Dequeue();
                r.resetStart();
                Border rb = getBorderInUICollection(QueueParkingLot.Children, r);
                QueueParkingLot.Children.Remove(rb);
                pushCar(r, builder);
            }
            ParkingLotInfo.Text = builder.ToString();
            CarName.Text = "";
        }

        private bool popCar(string name, StringBuilder builder)
        {
            //临时栈用来存放临时出去的车
            Stack<Car> tempCarStack = new Stack<Car>();
            Car Pc = null;

            while (carStack.Count() != 0)
            {
                Car tempCar = carStack.Pop();
                if (tempCar.getName() == name)
                {
                    Pc = tempCar;
                    break;
                }
                tempCarStack.Push(tempCar);
            }
            //将临时出来的车辆依次回排到停车场
            while (tempCarStack.Count() != 0)
            {
                Car tempCar = tempCarStack.Pop();
                carStack.Push(tempCar);
            }

            if (Pc == null)
            {
                builder.Append("没有相关车辆的信息。");
                return false;
            }

            Border bd = getBorderInUICollection(StackParkingLot.Children, Pc);
            StackParkingLot.Children.Remove(bd);

            Duration duration = Pc.getOut(); //获取汽车出停车场的时间
            builder.Append("下面是离开停车场的车辆信息：\n");
            builder.Append("车辆牌号： " + Pc.getName());
            builder.Append("\n出场的时刻: " + Pc.getEnd().ToString());
            builder.Append("\n停车时长: " + duration.ToString() + " s");
            builder.Append("\n停车花费: " + Pc.getCost() + "元。\n");
            return true;
        }

        private Border GetNewBorder(Car c)
        {
            Border myBorder = new Border();
            myBorder.Background = Brushes.SkyBlue;
            myBorder.BorderBrush = Brushes.Black;
            myBorder.BorderThickness = new Thickness(1);
            myBorder.Margin = new Thickness(16, 16, 16, 0);
            myBorder.Width = 100;
            myBorder.Height = 30;
            TextBlock txt = new TextBlock();
            txt.Foreground = Brushes.Black;
            txt.FontSize = 12;
            txt.Text = c.getName();
            myBorder.Child = txt;
            return myBorder;
        }

        private Border getBorderInUICollection(UIElementCollection ec, Car r)
        {
            Border bd = null;
            foreach (Border b in ec)
            {
                TextBlock tb = (TextBlock)b.Child;
                if (tb.Text == r.getName())
                {
                    bd = b;
                    break;
                }
            }
            return bd;
        }
    }

    public class Car
    {
        private string name;
        private DateTime start;
        private DateTime end;
        public Car(string l, DateTime s)
        {
            name = l;
            start = s;
        }

        public string getName()
        {
            return name;
        }

        public void resetStart()
        {
            start = DateTime.Now;
        }

        public DateTime getStart()
        {
            return start;
        }

        public DateTime getEnd()
        {
            return end;
        }

        public Duration getOut()
        {
            end = DateTime.Now;
            Duration duration = end - start;
            return duration;
        }

        public int getCost()
        {
            return (end - start).Seconds * 2;
        }
    }
}
