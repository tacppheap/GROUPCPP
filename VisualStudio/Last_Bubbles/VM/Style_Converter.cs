using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows;
using Last_Bubbles.Models;

namespace Last_Bubbles.VM
{
    [ValueConversion( typeof(M_BALL) , typeof(Style) )]
    class Style_Converter: IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            var ball = (M_BALL)value;
            Style Ball_Style = (Style)Application.Current.FindResource("Default_Ball"); 
            switch ((bool)ball.IsChecked.ob)
            {
                case true:
                    {
                        switch ((int)ball.b_t)
                        {
                            case 0:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Checked_Red_Ball");
                                    break;
                                }
                            case 1:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Checked_Green_Ball");
                                    break;
                                }
                            case 2:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Checked_Blue_Ball");
                                    break;
                                }
                            case 3:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Checked_Yellow_Ball");
                                    break;
                                }
                            default:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Default_Ball");
                                    break;
                                }
                        }

                        break;
                    }

                case false:
                    {
                        switch ((int)ball.b_t)
                        {
                            case 0:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Red_Ball");
                                    break;
                                }
                            case 1:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Green_Ball");
                                    break;
                                }
                            case 2:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Blue_Ball");
                                    break;
                                }
                            case 3:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Yellow_Ball");
                                    break;
                                }
                            default:
                                {
                                    Ball_Style = (Style)Application.Current.FindResource("Default_Ball");
                                    break;
                                }
                        }

                        break;
                    }

            }            

            return Ball_Style;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
