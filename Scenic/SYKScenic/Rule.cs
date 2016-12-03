using System;
using System.Windows.Controls;
using System.Globalization;
namespace SYKScenic
{
    public class Rule : ValidationRule
    {
        public int Min { get; set; }
        public int Max { get; set; }

        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            var popuDis = 0;

            try
            {
                if (((string)value).Length > 0)
                    popuDis = int.Parse((string)value);
            }
            catch (Exception e)
            {
                Console.WriteLine(new ValidationResult(false, "Illegal characters or " + e.Message));
            }

            if ((popuDis < Min) || (popuDis > Max))
            {
                Console.WriteLine(new ValidationResult(false,
                    "Please enter an age in the range: " + Min + " - " + Max + "."));
            }
            return new ValidationResult(true, null);
        }
    }
}
