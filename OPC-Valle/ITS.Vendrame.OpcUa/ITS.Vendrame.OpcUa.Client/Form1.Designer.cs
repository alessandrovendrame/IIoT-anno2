
namespace ITS.Vendrame.OpcUa.Client
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lblCPU = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lblRAM = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtCpu = new System.Windows.Forms.TextBox();
            this.txtRam = new System.Windows.Forms.TextBox();
            this.btnSendCpu = new System.Windows.Forms.Button();
            this.btnSendRam = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblCPU
            // 
            this.lblCPU.AutoSize = true;
            this.lblCPU.Location = new System.Drawing.Point(62, 13);
            this.lblCPU.Name = "lblCPU";
            this.lblCPU.Size = new System.Drawing.Size(17, 20);
            this.lblCPU.TabIndex = 0;
            this.lblCPU.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(39, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "CPU:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 43);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "RAM:";
            // 
            // lblRAM
            // 
            this.lblRAM.AutoSize = true;
            this.lblRAM.Location = new System.Drawing.Point(62, 43);
            this.lblRAM.Name = "lblRAM";
            this.lblRAM.Size = new System.Drawing.Size(17, 20);
            this.lblRAM.TabIndex = 3;
            this.lblRAM.Text = "0";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnSendRam);
            this.groupBox1.Controls.Add(this.btnSendCpu);
            this.groupBox1.Controls.Add(this.txtRam);
            this.groupBox1.Controls.Add(this.txtCpu);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Location = new System.Drawing.Point(13, 87);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(342, 351);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "EditNodes";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 13);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 20);
            this.label3.TabIndex = 1;
            this.label3.Text = "CPU:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 39);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(39, 20);
            this.label4.TabIndex = 5;
            this.label4.Text = "CPU:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 84);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 20);
            this.label5.TabIndex = 5;
            this.label5.Text = "RAM:";
            // 
            // txtCpu
            // 
            this.txtCpu.Location = new System.Drawing.Point(62, 39);
            this.txtCpu.Name = "txtCpu";
            this.txtCpu.Size = new System.Drawing.Size(190, 27);
            this.txtCpu.TabIndex = 6;
            // 
            // txtRam
            // 
            this.txtRam.Location = new System.Drawing.Point(62, 81);
            this.txtRam.Name = "txtRam";
            this.txtRam.Size = new System.Drawing.Size(190, 27);
            this.txtRam.TabIndex = 7;
            // 
            // btnSendCpu
            // 
            this.btnSendCpu.Location = new System.Drawing.Point(258, 38);
            this.btnSendCpu.Name = "btnSendCpu";
            this.btnSendCpu.Size = new System.Drawing.Size(59, 29);
            this.btnSendCpu.TabIndex = 8;
            this.btnSendCpu.Text = "Send";
            this.btnSendCpu.UseVisualStyleBackColor = true;
            this.btnSendCpu.Click += new System.EventHandler(this.btnSendCpu_Click);
            // 
            // btnSendRam
            // 
            this.btnSendRam.Location = new System.Drawing.Point(258, 81);
            this.btnSendRam.Name = "btnSendRam";
            this.btnSendRam.Size = new System.Drawing.Size(59, 29);
            this.btnSendRam.TabIndex = 9;
            this.btnSendRam.Text = "Send";
            this.btnSendRam.UseVisualStyleBackColor = true;
            this.btnSendRam.Click += new System.EventHandler(this.btnSendRam_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(410, 450);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.lblRAM);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblCPU);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblCPU;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblRAM;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnSendRam;
        private System.Windows.Forms.Button btnSendCpu;
        private System.Windows.Forms.TextBox txtRam;
        private System.Windows.Forms.TextBox txtCpu;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
    }
}

