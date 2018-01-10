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
    public class VM_BOARD : INotifyPropertyChanged
    {
        /*****************************************************************************/
        public int NUM_ROW = 10;
        public int NUM_COL = 10;

        /*****************************************************************************/

        private string Score = "0";
        private string TScore = "0";
        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            if (PropertyChanged != null) PropertyChanged(this, e);
        }

        public string score
        {
            get { return Score; }
            set { Score = value; OnPropertyChanged(new PropertyChangedEventArgs("score")); }
        }

        public string Tscore
        {
            get { return TScore; }
            set { TScore = value; OnPropertyChanged(new PropertyChangedEventArgs("Tscore")); }
        }

        public int int_score
        {
            get { return board.Num_Checked_Balls.ob; }
            set { board.Num_Checked_Balls.ob = value; score = value.ToString(); }
        }

        /*****************************************************************************/
        public M_BOARD board;

        public List<VM_BALL> VM_Ball_List = new List<VM_BALL>();

        public VM_BOARD(int nr, int nc)
        {
            NUM_COL = nc;
            NUM_ROW = nr;

            board = new M_BOARD(NUM_ROW, NUM_COL);
            board.Num_Checked_Balls.ChEv += VM_Board_Num_Checked_Handler;
            board.Num_Killed_Balls.ChEv += VM_Board_Num_Killed_Handler;
            for(int y = 0; y < NUM_ROW; y++)
                for (int x = 0; x < NUM_COL; x++)
                {
                    VM_Ball_List.Add(new VM_BALL(board[y, x]));
                }

        }

        public void VM_Board_Num_Checked_Handler(object source, Changeable_Ob<int>.ChEvArgs arg)
        {
            score = board.Num_Checked_Balls.ob.ToString();
        }
        public void VM_Board_Num_Killed_Handler(object source, Changeable_Ob<int>.ChEvArgs arg)
        {
            Tscore = board.Num_Killed_Balls.ob.ToString();
        }
    }
}
