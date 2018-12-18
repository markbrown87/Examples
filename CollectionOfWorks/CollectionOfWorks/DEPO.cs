using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CollectionOfWorks
{
    public partial class DEPO : Form
    {
        public DEPO()
        {
            InitializeComponent();
        }

        // Insert the code needed to actually calculate the numbers for the departments
        // RULES: 
        //      - PoliceDepo wants even numbers (Must have one even number)
        //      - All three departments must equal 12 in total
        //      - Numbers must be between 1 - 7 and must be Unique of other departments
        private void GenerateButton_MouseClick(object sender, MouseEventArgs e)
        {
            ResponseBox.Text = "Departments List:" + Environment.NewLine;

            for (int i = 1; i < 8; ++i)
            {
                for(int j = 1; j < 8; ++j)
                {
                    for(int m = 1; m < 8; ++m)
                    {
                        // Checks if the values are equal to 12 THEN checks if they are not the same -> IFF accepted is it printed out
                        if((i + j + m) == 12 && ((i != j) || (i != m) || (j != m)))
                        {
                            ResponseBox.Text += i.ToString() + " " + j.ToString() + " " + m.ToString() + Environment.NewLine;
                        }
                    }
                }
            }

        }
        private void DEPO_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void ReturnButton_MouseClick(object sender, MouseEventArgs e)
        {
            StartWindow sw = new StartWindow();
            Hide();
            sw.ShowDialog();
            Close();
        }
    }
}
