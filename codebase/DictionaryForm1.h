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
	/// Summary for DictionaryForm1
	/// </summary>
	public ref class DictionaryForm1 : public System::Windows::Forms::Form
	{
	private:
		Form^ parent;
	public:
		DictionaryForm1(void)
		{
			InitializeComponent();
			fill_list();
			//
			//TODO: Add the constructor code here
			//
		}
		DictionaryForm1(Form^ par)
		{
			parent = par;
			InitializeComponent();
			fill_list();
			//
			//TODO: Add the constructor code here
			//
		}
		void fill_list(void)
		{
			char temp[100];
			FILE *fp = fopen("selected_model.txt","r");
			fscanf(fp,"%s",temp);
			fclose(fp);
			char file_name[200];
			strcpy(file_name,"live_models/");
			strcat(file_name,temp);
			strcat(file_name,"/vocab.txt");
			fp = fopen(file_name,"r");
			while(fscanf(fp,"%s",file_name)==1)
				vocabList->Items->Add(gcnew String(file_name));	
			fclose(fp);
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DictionaryForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  vocabList;
	protected: 

	protected: 

	protected: 
	private: System::Windows::Forms::Label^  lblVocab;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(DictionaryForm1::typeid));
			this->vocabList = (gcnew System::Windows::Forms::ListBox());
			this->lblVocab = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// vocabList
			// 
			this->vocabList->BackColor = System::Drawing::Color::LightCyan;
			this->vocabList->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->vocabList->ForeColor = System::Drawing::Color::Maroon;
			this->vocabList->FormattingEnabled = true;
			this->vocabList->ItemHeight = 22;
			this->vocabList->Location = System::Drawing::Point(82, 75);
			this->vocabList->Name = L"vocabList";
			this->vocabList->Size = System::Drawing::Size(214, 158);
			this->vocabList->TabIndex = 0;
			// 
			// lblVocab
			// 
			this->lblVocab->BackColor = System::Drawing::Color::Transparent;
			this->lblVocab->Font = (gcnew System::Drawing::Font(L"Consolas", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblVocab->ForeColor = System::Drawing::Color::Black;
			this->lblVocab->Location = System::Drawing::Point(76, 35);
			this->lblVocab->Name = L"lblVocab";
			this->lblVocab->Size = System::Drawing::Size(220, 37);
			this->lblVocab->TabIndex = 1;
			this->lblVocab->Text = L"VOCABULARY";
			this->lblVocab->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// DictionaryForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(393, 321);
			this->Controls->Add(this->lblVocab);
			this->Controls->Add(this->vocabList);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"DictionaryForm1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Vocabulary";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &DictionaryForm1::DictionaryForm1_FormClosed);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void DictionaryForm1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 parent->Show();
			 }
};
}
