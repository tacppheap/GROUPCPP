using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Shapes;
using System.Windows;
using System.ComponentModel;
using System.Windows.Input;
using Last_Bubbles.Models;


namespace Last_Bubbles.VM
{
    public class VM_BALL : UIElement, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            if (PropertyChanged != null) PropertyChanged(this, e);
        }


        public VM_BALL(M_BALL b)
        {
            Ball = b;
            b.y.ChEv += VM_BALL_Y_Handler;
            b.x.ChEv += VM_BALL_X_Handler;
            b.IsChecked.ChEv += VM_BALL_Checked_Handler;
            b.IsKilled.ChEv += VM_BALL_Kill_Handler;


        }
        public static readonly RoutedEvent RightEvent = EventManager.RegisterRoutedEvent
            (
                "Right",
                RoutingStrategy.Bubble,
                typeof(RoutedEventHandler),
                typeof(VM_BALL)
            );

        public event RoutedEventHandler Right
        {
            add
            {
                AddHandler(RightEvent, value);
            }
            remove
            {
                RemoveHandler(RightEvent, value);
            }
        }

        public static readonly RoutedEvent FallEvent = EventManager.RegisterRoutedEvent
            (
                "Fall",
                RoutingStrategy.Bubble,
                typeof(RoutedEventHandler),
                typeof (VM_BALL)
            );

        public event RoutedEventHandler Fall
        {
            add
            {
                AddHandler(FallEvent, value);
            }
            remove
            {
                RemoveHandler(FallEvent, value);
            }
        }


        public static readonly RoutedEvent KillEvent = EventManager.RegisterRoutedEvent
            (
                "Kill",
                RoutingStrategy.Bubble,
                typeof(RoutedEventHandler),
                typeof(VM_BALL)
            );

        public event RoutedEventHandler Kill
        {
            add
            {
                AddHandler(KillEvent, value);
            }
            remove
            {
                RemoveHandler(KillEvent, value);
            }
        }
    
        private int NEW_B;
        public double new_b
        {
            get { return NEW_B; }
            set { NEW_B = (int)value; OnPropertyChanged(new PropertyChangedEventArgs("new_b")); }
        }
        private int NEW_BX;
        public double new_bx
        {
            get { return NEW_BX; }
            set { NEW_BX = (int)value; OnPropertyChanged(new PropertyChangedEventArgs("new_bx")); }
        }
        private M_BALL Ball;
        public M_BALL ball
        {
            get { return Ball; }
            set { Ball = value; }
        }

        public bool IsChecked
        {
            get { return ball.IsChecked.ob; }
            set { ball.IsChecked.ob = value; }
        }

        public bool IsKilled
        {
            get { return ball.IsKilled.ob; }
            set {  ball.IsKilled.ob = value; }
        }



        public void VM_BALL_Checked_Handler(object source, Changeable_Ob<bool>.ChEvArgs arg)
        {
            OnPropertyChanged(new PropertyChangedEventArgs("ball"));
        }


        public void VM_BALL_Kill_Handler(object source, Changeable_Ob<bool>.ChEvArgs arg)
        {
            RoutedEventArgs e = new RoutedEventArgs(KillEvent, this);
            RaiseEvent(e);

        }

        public void VM_BALL_Y_Handler(object source, Changeable_Ob<int>.ChEvArgs arg)
        {
            new_b = (arg.owner as M_BALL).y.ob;
            RoutedEventArgs e = new RoutedEventArgs(FallEvent, this);
            RaiseEvent(e);
            
        }

        public void VM_BALL_X_Handler(object source, Changeable_Ob<int>.ChEvArgs arg)
        {
            new_bx = (arg.owner as M_BALL).x.ob;
            RoutedEventArgs e = new RoutedEventArgs(RightEvent, this);
            RaiseEvent(e);

        }


    }
}
