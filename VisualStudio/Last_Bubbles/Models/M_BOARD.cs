using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Last_Bubbles.Models
{
        public enum BALLTYPE : int { Red, Green, Blue, Yellow, Empty }

        public class M_BALL
        {

            public Changeable_Ob<int> x;
            public Changeable_Ob<int> y;
            public BALLTYPE b_t;
            public Changeable_Ob<bool> IsChecked;
            public Changeable_Ob<bool> IsKilled;
            public M_BALL()
            {
                x = new Changeable_Ob<int>(0, this);
                y = new Changeable_Ob<int>(0, this);
                IsChecked = new Changeable_Ob<bool>(false, this);
                IsKilled = new Changeable_Ob<bool>(false, this);
            }
        }

        public class M_BOARD
        {
            public int Max_Row;
            public int Max_Column;
            private List<M_BALL> ball_list;
            private int Max_Num_Colors = 4;
            private int Num_OUT_Game_Columns = 0;
            public Changeable_Ob<int> Num_Killed_Balls;

            public M_BOARD(int M_R, int M_C)
            {
                Max_Row = M_R;
                Max_Column = M_C;

                ball_list = new List<M_BALL>();
                Num_Checked_Balls = new Changeable_Ob<int>(0, this);
                Num_Handle_Balls  = new Changeable_Ob<int>(0, this);
                Num_Killed_Balls  = new Changeable_Ob<int>(0, this);

                for (int num_ball = 0; num_ball < Max_Row * Max_Column; num_ball++)
                {
                    ball_list.Add(new M_BALL());
                }

                Random rnd;
                rnd = new Random();

                for (int num_row = 0; num_row < Max_Row; num_row++)
                    for (int num_col = 0; num_col < Max_Column; num_col++)
                    {
                        this[num_row, num_col].x.ob = num_col;
                        this[num_row, num_col].y.ob = num_row;
                        this[num_row, num_col].b_t = (BALLTYPE)rnd.Next(0, Max_Num_Colors);
                        this[num_row, num_col].IsChecked.ChEv += Board_Checked_Handler;
                        this[num_row, num_col].IsKilled.ChEv += Board_Killed_Handler;
                        Num_Handle_Balls.ChEv += Board_Num_Handle_Handler;
                    }

            }

            public M_BALL this[int num_row, int num_col]
            {
                get
                {
                    if ((num_col < Max_Column) && (num_col >= 0) && (num_row < Max_Row) && (num_row >= 0))
                    {
                        return ball_list[num_row * Max_Column + num_col];
                    }
                    else
                    {
                        return null;
                    }

                }
                set
                {
                    if ((num_row < Max_Row) && (num_col < Max_Column) && (num_col >= 0) && (num_row >= 0))
                        ball_list[num_row * Max_Column + num_col] = value;
                }

            }


            private void Glue_Balls(int num_col)
            {
                M_BALL ball;
                M_BALL bot;
                for (int num_row = Max_Row - 2; num_row >= 0; num_row--)
                {
                    if ((this[num_row, num_col] != null) && (this[num_row + 1, num_col] == null))
                    {
                        ball = this[num_row, num_col];
                        do
                        {
                            Move_Ball_Down(ball);
                            bot = this[ball.y.ob + 1, ball.x.ob];

                        } while ((bot == null) && (ball.y.ob != Max_Row - 1));

                    }
                }

            }


            private void Move_Ball_Down(M_BALL ball)
            {
                int x;
                int y;
                x = ball.x.ob;
                y = ball.y.ob;
                if (y < Max_Row - 1)
                {
                    this[y + 1, x] = this[y, x];
                    this[y + 1, x].y.ob = y + 1;
                    this[y, x] = null;
                }
            }


            private bool Column_Is_Clear(int num_col)
            {
                bool clear = true;

                for (int num_row = 0; num_row < Max_Row; num_row++)
                    if (this[num_row, num_col] != null) { clear = false; };

                return clear;
            }

            private void Fill_Empty_Column(int empty_col)
            {
                for (int num_col = empty_col - 1; num_col >= Num_OUT_Game_Columns; num_col--)
                {
                    for (int num_row = 0; num_row < Max_Row; num_row++)
                    {
                        if (this[num_row, num_col] != null)
                            this[num_row, num_col].x.ob = num_col + 1;

                        this[num_row, num_col + 1] = this[num_row, num_col];


                    }
                }

            }

            /************************************Handlers****************************************/

            public Changeable_Ob<int> Num_Checked_Balls;

            public void Board_Checked_Handler(object source, Changeable_Ob<bool>.ChEvArgs arg)
            {
                Num_Checked_Balls.ob++;
                M_BALL ball = (M_BALL)arg.owner;
                int x = ball.x.ob;
                int y = ball.y.ob;

                M_BALL top = this[y - 1, x];
                if ((top != null) &&
                    (top.b_t == ball.b_t) &&
                    (top.IsChecked.ob != arg.val))
                {
                    top.IsChecked.ob = arg.val;
                }

                M_BALL left = this[y, x - 1];
                if ((left != null) &&
                    (left.b_t == ball.b_t) &&
                    (left.IsChecked.ob != arg.val))
                {
                    left.IsChecked.ob = arg.val;
                }

                M_BALL right = this[y, x + 1];
                if ((right != null) &&
                    (right.b_t == ball.b_t) &&
                    (right.IsChecked.ob != arg.val))
                {
                    right.IsChecked.ob = arg.val;
                }

                M_BALL bot = this[y + 1, x];
                if ((bot != null) &&
                    (bot.b_t == ball.b_t) &&
                    (bot.IsChecked.ob != arg.val))
                {
                    bot.IsChecked.ob = arg.val;
                }
            }


            public Changeable_Ob<int> Num_Handle_Balls;


            public void Board_Killed_Handler(object source, Changeable_Ob<bool>.ChEvArgs arg)
            {

                Num_Handle_Balls.ob++;

                M_BALL ball = (M_BALL)arg.owner;
                int x = ball.x.ob;
                int y = ball.y.ob;


                if ((arg.val == true) && (Num_Checked_Balls.ob > 1))
                {
                    this[y, x] = null;
                    Num_Killed_Balls.ob++;

                    M_BALL top = this[y - 1, x];

                    if ((top != null) &&
                        (top.IsChecked.ob) &&
                        (!top.IsKilled.ob))
                    {
                        top.IsKilled.ob = true;
                    }

                    M_BALL left = this[y, x - 1];
                    if ((left != null) &&
                        (left.IsChecked.ob) &&
                        (!left.IsKilled.ob))
                    {
                        left.IsKilled.ob = true;
                    }

                    M_BALL right = this[y, x + 1];
                    if ((right != null) &&
                        (right.IsChecked.ob) &&
                        (!right.IsKilled.ob))
                    {
                        right.IsKilled.ob = true;
                    }

                    M_BALL bot = this[y + 1, x];
                    if ((bot != null) &&
                        (bot.IsChecked.ob) &&
                        (!bot.IsKilled.ob))
                    {
                        bot.IsKilled.ob = true;
                    }




                }
                Num_Handle_Balls.ob--;
            }



           



            public void Board_Num_Handle_Handler(object source, Changeable_Ob<int>.ChEvArgs arg)
            {
                if (Num_Handle_Balls.ob == 0)
                {


                    for (int num_col = Max_Column - 1; num_col >= Num_OUT_Game_Columns; num_col--)
                    {
                        if (Column_Is_Clear(num_col))
                        {
                            Fill_Empty_Column(num_col);

                            for (int num_row = 0; num_row < Max_Row; num_row++)
                                this[num_row, Num_OUT_Game_Columns] = null;

                            num_col++;
                            Num_OUT_Game_Columns++;
                        }
                        else
                        {
                            Glue_Balls(num_col);
                        }
                    }
                }
            }
        }
}
