namespace CollectionOfWorks
{
    partial class DEPO
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.GenerateButton = new System.Windows.Forms.Button();
            this.ResponseBox = new System.Windows.Forms.TextBox();
            this.ReturnButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // GenerateButton
            // 
            this.GenerateButton.Location = new System.Drawing.Point(137, 12);
            this.GenerateButton.Name = "GenerateButton";
            this.GenerateButton.Size = new System.Drawing.Size(88, 23);
            this.GenerateButton.TabIndex = 0;
            this.GenerateButton.Text = "Execute Code";
            this.GenerateButton.UseVisualStyleBackColor = true;
            this.GenerateButton.MouseClick += new System.Windows.Forms.MouseEventHandler(this.GenerateButton_MouseClick);
            // 
            // ResponseBox
            // 
            this.ResponseBox.Location = new System.Drawing.Point(12, 12);
            this.ResponseBox.Multiline = true;
            this.ResponseBox.Name = "ResponseBox";
            this.ResponseBox.Size = new System.Drawing.Size(119, 494);
            this.ResponseBox.TabIndex = 1;
            // 
            // ReturnButton
            // 
            this.ReturnButton.Location = new System.Drawing.Point(137, 41);
            this.ReturnButton.Name = "ReturnButton";
            this.ReturnButton.Size = new System.Drawing.Size(88, 23);
            this.ReturnButton.TabIndex = 2;
            this.ReturnButton.Text = "Return";
            this.ReturnButton.UseVisualStyleBackColor = true;
            this.ReturnButton.MouseClick += new System.Windows.Forms.MouseEventHandler(this.ReturnButton_MouseClick);
            // 
            // DEPO
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(231, 516);
            this.Controls.Add(this.ReturnButton);
            this.Controls.Add(this.ResponseBox);
            this.Controls.Add(this.GenerateButton);
            this.Name = "DEPO";
            this.Text = "DEPO";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.DEPO_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button GenerateButton;
        private System.Windows.Forms.TextBox ResponseBox;
        private System.Windows.Forms.Button ReturnButton;
    }
}