using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Login
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void user_Click(object sender, EventArgs e)
        {

        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            string usuario = textBox1.Text;
            string contrasena = textBox2.Text;

            if (usuario == "admin" && contrasena == "1234")
            {
                mensaje.Text = "¡Bienvenido!";
            }
            else
            {
                mensaje.Text = "Usuario o contraseña incorrectos.";
            }
        }
    }
}
