using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Last_Bubbles.Models
{
   
        public class Changeable_Ob<T>
        {
            private T val;

            private object owner;
            
            public Changeable_Ob(T o, Object O)
            {
                val = o;
                owner = O;
            }

            public T ob
            {
                get
                {
                    return val;
                }

                set
                {
                    val = value;
                    OnChEv();
                }

            }

            public class ChEvArgs : EventArgs
            {
                public T val;
                public Object owner;
            }

            public event EventHandler<ChEvArgs> ChEv;
            private ChEvArgs ch_ev_args = new ChEvArgs();

            public void OnChEv()
            {

                if (ChEv != null)
                {
                    ch_ev_args.val = val;
                    ch_ev_args.owner = owner;
                    ChEv(this, ch_ev_args);
                }
            }

         }
    
}
