using System.Globalization;
using System.Windows;

namespace Case4Calculator;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
    }

    private void Sum_Click(object sender, RoutedEventArgs e)
    {
        Calculate((left, right) => left + right, "Сумма");
    }

    private void Subtract_Click(object sender, RoutedEventArgs e)
    {
        Calculate((left, right) => left - right, "Разность");
    }

    private void Multiply_Click(object sender, RoutedEventArgs e)
    {
        Calculate((left, right) => left * right, "Произведение");
    }

    private void Divide_Click(object sender, RoutedEventArgs e)
    {
        Calculate(
            (left, right) =>
            {
                if (right == 0)
                {
                    throw new DivideByZeroException();
                }

                return left / right;
            },
            "Деление");
    }

    private void Calculate(Func<double, double, double> operation, string operationName)
    {
        if (!TryReadNumbers(out double first, out double second))
        {
            ResultTextBlock.Text = "Ошибка: в оба поля нужно ввести корректные числа.";
            return;
        }

        try
        {
            double result = operation(first, second);
            ResultTextBlock.Text = $"{operationName}: {result}";
        }
        catch (DivideByZeroException)
        {
            ResultTextBlock.Text = "Ошибка: деление на ноль недопустимо.";
        }
    }

    private bool TryReadNumbers(out double first, out double second)
    {
        var culture = CultureInfo.InvariantCulture;
        bool firstValid = double.TryParse(FirstNumberTextBox.Text.Replace(',', '.'), NumberStyles.Float, culture, out first);
        bool secondValid = double.TryParse(SecondNumberTextBox.Text.Replace(',', '.'), NumberStyles.Float, culture, out second);

        return firstValid && secondValid;
    }
}
