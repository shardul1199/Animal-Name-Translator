#pragma once
//#include "stdafx.h"

#include <Windows.h>

#include <msclr\marshal_cppstd.h>

#include "Data.h"

//#include <msclr\marshal_cppstd.h>

namespace Speech_Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for Form2
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form^ parent;
		Paths^ dat;
	private: System::Windows::Forms::PictureBox^  picBox;
	private: System::Windows::Forms::Label^  lblAnimal;
	private: System::Windows::Forms::PictureBox^  btnPlay;
	private: System::Windows::Forms::Timer^  timer1;


	public: 

	public: 

	public: 

	public: 

	public: 

	private: System::Windows::Forms::RichTextBox^  richText;
	public: 

	public: 
		static int interval1 = 0;
			 
		Form2(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		Form2(Form^ form,Paths^ dat)
		{
			parent = form;
			this->dat = dat;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnExit;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form2::typeid));
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->richText = (gcnew System::Windows::Forms::RichTextBox());
			this->picBox = (gcnew System::Windows::Forms::PictureBox());
			this->lblAnimal = (gcnew System::Windows::Forms::Label());
			this->btnPlay = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->btnPlay))->BeginInit();
			this->SuspendLayout();
			// 
			// btnExit
			// 
			this->btnExit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnExit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnExit->Font = (gcnew System::Drawing::Font(L"Candara", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnExit->ForeColor = System::Drawing::Color::Black;
			this->btnExit->Location = System::Drawing::Point(373, 627);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(106, 44);
			this->btnExit->TabIndex = 0;
			this->btnExit->Text = L"E&xit";
			this->btnExit->UseVisualStyleBackColor = false;
			this->btnExit->Click += gcnew System::EventHandler(this, &Form2::button1_Click);
			// 
			// richText
			// 
			this->richText->BackColor = System::Drawing::Color::Yellow;
			this->richText->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richText->EnableAutoDragDrop = true;
			this->richText->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->richText->ForeColor = System::Drawing::Color::DarkRed;
			this->richText->Location = System::Drawing::Point(97, 350);
			this->richText->Name = L"richText";
			this->richText->ReadOnly = true;
			this->richText->Size = System::Drawing::Size(684, 254);
			this->richText->TabIndex = 2;
			this->richText->Text = L"";
			// 
			// picBox
			// 
			this->picBox->BackColor = System::Drawing::Color::Transparent;
			this->picBox->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->picBox->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picBox.Image")));
			this->picBox->ImageLocation = L"";
			this->picBox->Location = System::Drawing::Point(310, 40);
			this->picBox->Name = L"picBox";
			this->picBox->Size = System::Drawing::Size(279, 222);
			this->picBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picBox->TabIndex = 3;
			this->picBox->TabStop = false;
			this->picBox->Click += gcnew System::EventHandler(this, &Form2::picBox_Click);
			// 
			// lblAnimal
			// 
			this->lblAnimal->BackColor = System::Drawing::Color::Transparent;
			this->lblAnimal->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblAnimal->ForeColor = System::Drawing::Color::Black;
			this->lblAnimal->Location = System::Drawing::Point(231, 285);
			this->lblAnimal->Name = L"lblAnimal";
			this->lblAnimal->Size = System::Drawing::Size(417, 53);
			this->lblAnimal->TabIndex = 4;
			this->lblAnimal->Text = L"label1";
			this->lblAnimal->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnPlay
			// 
			this->btnPlay->BackColor = System::Drawing::Color::Transparent;
			this->btnPlay->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnPlay.Image")));
			this->btnPlay->Location = System::Drawing::Point(267, 249);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(37, 33);
			this->btnPlay->TabIndex = 5;
			this->btnPlay->TabStop = false;
			this->btnPlay->Click += gcnew System::EventHandler(this, &Form2::btnPlay_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form2::timer1_Tick);
			// 
			// Form2
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(894, 683);
			this->Controls->Add(this->btnPlay);
			this->Controls->Add(this->lblAnimal);
			this->Controls->Add(this->picBox);
			this->Controls->Add(this->richText);
			this->Controls->Add(this->btnExit);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Form2";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Limo";
			this->TransparencyKey = System::Drawing::Color::White;
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form2::Form2_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Form2::Form2_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->btnPlay))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form2_Load(System::Object^  sender, System::EventArgs^  e) {
				 
				 Image^ img;
				 img = gcnew Bitmap(dat->getImagePath());
				 picBox->Image = img;
				 richText->Text = dat->getDescription();
				 lblAnimal->Text = dat->getName();
				 timer1->Start();
				 

			 }
	private: System::Void Form2_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 parent->Show();
			 }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 parent->Show();
				 this->Close();
			 }
	private: System::Void picBox_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void btnPlay_Click(System::Object^  sender, System::EventArgs^  e) {
			pin_ptr<const wchar_t> wch = PtrToStringChars(dat->getAudioPath());
				 size_t origsize = wcslen(wch) + 1;
				  const size_t newsizew = origsize;
					wchar_t* wcstring = new wchar_t[newsizew];
					wcscpy_s(wcstring, newsizew, wch);
				PlaySound(wcstring,NULL,SND_NOSTOP);
				delete []wcstring;
				pin_ptr<const wchar_t> wch1 = PtrToStringChars(dat->getAnimalSounds());
				 size_t origsize1 = wcslen(wch1) + 1;
				const size_t newsizew1 = origsize1;
				wchar_t* wcstring1 = new wchar_t[newsizew1];
				wcscpy_s(wcstring1, newsizew1, wch1);
				PlaySound(wcstring1,NULL,SND_NOSTOP);
				delete []wcstring1;
			// PlaySound(TEXT(dat->getAudioPath()),NULL,SND_ASYNC);
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 interval1++;
			 if(interval1 >= 1)
			 {
				 pin_ptr<const wchar_t> wch = PtrToStringChars(dat->getAudioPath());
				 size_t origsize = wcslen(wch) + 1;
				  const size_t newsizew = origsize;
					wchar_t* wcstring = new wchar_t[newsizew];
					wcscpy_s(wcstring, newsizew, wch);
				PlaySound(wcstring,NULL,SND_NOSTOP);
				delete []wcstring;
				pin_ptr<const wchar_t> wch1 = PtrToStringChars(dat->getAnimalSounds());
				 size_t origsize1 = wcslen(wch1) + 1;
				const size_t newsizew1 = origsize1;
				wchar_t* wcstring1 = new wchar_t[newsizew1];
				wcscpy_s(wcstring1, newsizew1, wch1);
				PlaySound(wcstring1,NULL,SND_NOSTOP);
				delete []wcstring1;
				 interval1 = 0;
				 timer1->Stop();
			 }
		 }
};
}
