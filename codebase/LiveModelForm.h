#pragma once
#include<stdio.h>
#include<string>
#include <vcclr.h>
namespace Speech_Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LiveModelForm
	/// </summary>
	public ref class LiveModelForm : public System::Windows::Forms::Form
	{
	private:
		Form^ parent;

		String^ selected_val;
		
	public:
		LiveModelForm(void)
		{
			InitializeComponent();
			fill_models();
			//
			//TODO: Add the constructor code here
			//
		}
		LiveModelForm(Form^ par)
		{
			parent = par;
			InitializeComponent();
			fill_models();
			//
			//TODO: Add the constructor code here
			//
		}
		void fill_models(void)
		{
			system("dir live_models /b /ad > live_models/ListOfModels.txt");
			FILE *fp = fopen("live_models/ListOfModels.txt","r");
			int num;
			fscanf(fp,"%d",&num);
			char file_name[100];
			char temp[200];
			strcpy(temp,"live_models/");
			int index = 0,default_index;
			FILE *tr;
			while(fscanf(fp,"%s",file_name)==1)
			{
				
				strcat(temp,file_name);
				strcat(temp,"/trained.txt");
				if(tr=fopen(temp,"r"))
				{
					fclose(tr);
					if(strcmp(file_name,"default")==0)
						default_index = index;
					models->Items->Add(gcnew String(file_name));
					index++;
				}
				strcpy(temp,"live_models/");
			}
			models->SelectedIndex = default_index;
			fclose(fp);
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LiveModelForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  models;


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->models = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Gold;
			this->button1->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(141, 159);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(129, 48);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Submit";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &LiveModelForm::button1_Click);
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Courier New", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(149, 53);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(121, 34);
			this->label2->TabIndex = 3;
			this->label2->Text = L"MODELS";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// models
			// 
			this->models->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->models->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->models->Location = System::Drawing::Point(85, 105);
			this->models->Name = L"models";
			this->models->Size = System::Drawing::Size(261, 26);
			this->models->TabIndex = 4;
			this->models->SelectedIndexChanged += gcnew System::EventHandler(this, &LiveModelForm::models_SelectedIndexChanged);
			// 
			// LiveModelForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Beige;
			this->ClientSize = System::Drawing::Size(425, 244);
			this->Controls->Add(this->models);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LiveModelForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LiveModelForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &LiveModelForm::LiveModelForm_FormClosed);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void LiveModelForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				
				 parent->Show();
			 }
private: System::Void models_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 selected_val = models->Text;

		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(MessageBox::Show("Selected Model : "+selected_val+"\nAre You Sure Want to Proceed ?","Selected Model",MessageBoxButtons::YesNo,MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
				{
					FILE *fw = fopen("selected_model.txt","w");
					pin_ptr<const wchar_t> wch = PtrToStringChars(selected_val);
					// Make a copy of the System::String as a multibyte
					// char* string. Allocate two bytes in the multibyte
					// output string for every wide character in the input
					// string, including space for a terminating null.
					size_t origsize = wcslen(wch) + 1;
					const size_t newsize = origsize * 2;
					size_t convertedChars = 0;
					char* nstring = new char[newsize];
					wcstombs_s(&convertedChars, nstring, newsize, wch, _TRUNCATE);
					fprintf(fw,"%s",nstring);
					delete []nstring;
					fclose(fw);
					this->Close();
					//parent->Show();

			 }
		 }
};
}
