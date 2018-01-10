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
using Last_Bubbles.VM;
using System.ComponentModel;


namespace Last_Bubbles.View
{
    /// <summary>
    /// Interaction logic for UCBALL.xaml
    /// </summary>
    public partial class UCBALL : UserControl, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            if (PropertyChanged != null) PropertyChanged(this, e);
        }
       public UCBALL()
        {
            InitializeComponent();
            this.DataContextChanged += (object sender, DependencyPropertyChangedEventArgs e) =>
            {
               (this.DataContext as VM_BALL).Kill += UCBALL_DEL_HANDLER;
               (this.DataContext as VM_BALL).PropertyChanged += UCBALL_PC_HANDLER;
            };

        }

        public static DependencyProperty Ball_StyleProperty = DependencyProperty.Register("Ball_Style", typeof(Style), typeof(UCBALL), new FrameworkPropertyMetadata()); 
        public static DependencyProperty Ball_WidthProperty= DependencyProperty.Register("Ball_Width", typeof(double), typeof(UCBALL), new FrameworkPropertyMetadata());
        public static DependencyProperty Ball_HeightProperty = DependencyProperty.Register("Ball_Height", typeof(double), typeof(UCBALL), new FrameworkPropertyMetadata());

        public Style Ball_Style
        {
            get { return (Style)GetValue(Ball_StyleProperty); }
            set { SetValue(Ball_StyleProperty, value); }
        }
        public double Ball_Width
        {
            get { return (double)GetValue(Ball_WidthProperty); }
            set { SetValue(Ball_WidthProperty, value); }
        }
        public double Ball_Height
        {
            get { return (double)GetValue(Ball_HeightProperty); }
            set { SetValue(Ball_HeightProperty, value); }
        }
        private double BALL_NewX;
        public double Ball_NewX
        {
            get { return BALL_NewX *Ball_Width; }
            set { BALL_NewX = value; OnPropertyChanged(new PropertyChangedEventArgs("Ball_NewX")); }
        }
        private double BALL_NewY;
        public double Ball_NewY
        {
            get { return BALL_NewY * Ball_Height; }
            set { BALL_NewY = value; OnPropertyChanged(new PropertyChangedEventArgs("Ball_NewY")); }
        }


        public static readonly RoutedEvent DelEvent = EventManager.RegisterRoutedEvent
    (
        "Del",
        RoutingStrategy.Bubble,
        typeof(RoutedEventHandler),
        typeof(UCBALL)
    );

        public event RoutedEventHandler Del
        {
            add
            {
                AddHandler(DelEvent, value);
            }
            remove
            {
                RemoveHandler(DelEvent, value);
            }
        }

        private void UCBALL_DEL_HANDLER(object sender, RoutedEventArgs e)
        {

            RoutedEventArgs deleted = new RoutedEventArgs(DelEvent, this);
            RaiseEvent(deleted);
        }

        private void UCBALL_PC_HANDLER(object sender, PropertyChangedEventArgs e)
        {

            if (e.PropertyName == "new_b")
            {
                Ball_NewY = (this.DataContext as VM_BALL).new_b;
            }
            if (e.PropertyName == "new_bx")
            {
                Ball_NewX = (this.DataContext as VM_BALL).new_bx;
            }
        }
    }
}
