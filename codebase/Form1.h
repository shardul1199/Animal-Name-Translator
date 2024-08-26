
#pragma once

#include "MyAudioRecorder.h"
//#include "Data.h"

//#include <msclr\marshal_cppstd.h>
#include "Form2.h"


#include "InputForm1.h"
//#include "model.h"
//#include "Form3.h"
#include "testing.h"
#include "AboutForm.h"
#include "DictionaryForm.h"
#include "DictionaryForm1.h"
#include "LiveModelForm.h"
namespace Speech_Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	int index=0;
	int interval = 0;
	bool error_flag = false;
	bool isDefault = true;
	char* animals[11] = {"","cat","dog","horse","lion","tiger","monkey","rabbit","goat"};
	std:: string animal_names[11] = {"","\"CAT(BILLI)\"","\"DOG(KUTTA)\"","\"HORSE(GHODA)\"","\"LION(SHER)\"","\"TIGER(BAGH)\"","\"MONKEY(BANDAR)\"","\"RABBIT(KHARGOSH)\"","\"GOAT(BAKRI)\""};
	std :: string imagePaths[11] ={"","images/cat.png","images/dog.png","images/horse.png","images/lion.png","images/tiger.png","images/monkey.png","images/rabbit.png","images/goat.png"};
	std :: string descriptions[11] ={
	"","A cat is a domestic animal but there are wild cats too. Cats are found in various colours. The eyes of the cat which are of gray colour shine at night. A cat has sharp claws. The food of the cat is rats, pigeons and birds. She is fond of milk. It can climb up a tree and can jump from one roof to the other. When she mews the rats run away, and she also kills them. In this way she keeps rats away from our house. She has soft fur. She gives birth to kittens once in a year. She is very afraid of dogs.Cat is a wonderful domestic animal. She is playful also. But whenever she is put in trouble she becomes very dangerous. But on the whole we can say that a cat is a loving animal.",
		"A dog is one of the helpful animals that consist of a fluffy hairy body. Dogs help in protecting a house from thieves and fraud people during the night. There are so many breeds available on earth. They love to enjoy their time with their owner and family. He also protects their family members from strangers. Instead, they remain gentle and loyal to their family. Dogs also enjoy morning and evening walk with their owners. They need fresh and healthy food for the better growth of their body. They can eat fresh milk and meat for building strength. Dogs also lick their owner to make the owner understand their love.",
		"The horse is a four-footed animal. Horses are of many colours. It lives on green grass, straw, fodder, and grams. It is found in all parts of the world. The horse has a long neck. It has four strong legs. It has a bushy tail. It has two long ears. It has two bright and large eyes. It can swim in the water. It can run fast. It has a big strong body. It is a brave animal. It has a fighting spirit. It is used for riding and hunting in old times. It has sharp hoofs. It gives out a neighing sound. It severs its master faithfully. This useful animal carries a heavy load on its back. It kept in a stable.",
		"The lion is a wild terrestrial animal called the king of the jungle. The lion is a strong animal with a strong body, a big head, a majestic mane and two fierce eyes. Lions are predatory animals and eat only after hunting. They have strong claws and sharp teeth, which help them hunt their prey and eat the flesh. Lions have yellowish grey skin colour with smooth hair, and an imperious roar which makes a lion unique. The footprints of lions are called pug-marks. Lions are found chiefly in grasslands, open woodlands or enclosed in zoos. Since they kill their own prey and hunt for food, they have the capacity to run fast.",
		"Tiger is a wild animal that lives in forests. It is a carnivorous mammal that preys on organisms like deer. They are quick-paced and are very fast. The body of tigers is in the color of red or orange with dark black stripes on the surface. They have a length of 6 to 10 feet and weight nearly 660 pounds when they reach maturity. Tigers have a ferocious roar, but they don’t interfere with humans unless they hit or cause them harm. These animals can be adorable while functioning on the web.",
		"Monkeys are the most common and naughtiest animals we’ve known. Always jumping about and playing with their mates, monkeys fascinate kids and adults alike. Therefore, it’s no wonder the topic is popular in classes 1, 2, and 3. This article has an essay on monkeys of various lengths for kids of all primary classes. Besides learning how to write an essay on monkeys in English, young kids will also learn various interesting facts about monkeys. ",
		"Rabbits are cute and furry little animals that all kids love and are common as pets in houses and farms. Fairly tales and moral stories also frequently feature rabbits as significant characters as everyone loves them. Children are thus familiar with these adorable animals and will have several ideas and thoughts to express. When teachers assign them an essay writing topic on rabbits, they may need a little help as this essay will require a few facts apart from their personal views. Let us help your child write an essay for classes 1, 2 and 3 on these little furry animals.",
		"Goats are domestic animals.A goat has two horns, skin laden with thick hairs, four legs, two eyes and sometimes a beard on the chin.A group of goats is called a herd. Goats are herbivorous animals that eat grass, leaves, plants etc.It gives us milk which is very rich in nutrients and effective in dengue fever.A male goat is called a Buck and a female goat Doe.The young one of the goat is called a kid.The famous breed of the goat are Jamunapari, Barbari, Sirohi."
	};
	std:: string audioPaths[11] = {"","audios/cat.wav","audios/dog.wav","audios/horse.wav","audios/lion.wav","audios/tiger.wav","audios/monkey.wav","audios/rabbit.wav","audios/goat.wav"};
	std:: string animalsounds[11] = {"","animal_sounds/cat.wav","animal_sounds/dog.wav","animal_sounds/horse.wav","animal_sounds/lion.wav","animal_sounds/tiger.wav","animal_sounds/monkey.wav","animal_sounds/rabbit.mp3","animal_sounds/goat.wav"};
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		
			
		public:
		String ^res;
		int searchAnimals(char *key)
		{
			for(int i=1;i<=8;i++)
				if(stricmp(key,animals[i])==0)return i;
			return -1;
		}
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 


	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  btnPlay;
	private: System::Windows::Forms::PictureBox^  btnRecord;
	private: System::Windows::Forms::Panel^  panel1;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  vocab;
	private: System::Windows::Forms::Button^  About;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  modelLabel;







	private: System::ComponentModel::IContainer^  components;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->btnPlay = (gcnew System::Windows::Forms::PictureBox());
			this->btnRecord = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->vocab = (gcnew System::Windows::Forms::Button());
			this->About = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->modelLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->btnPlay))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->btnRecord))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// btnPlay
			// 
			this->btnPlay->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnPlay.Image")));
			this->btnPlay->Location = System::Drawing::Point(419, 28);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(50, 50);
			this->btnPlay->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->btnPlay->TabIndex = 1;
			this->btnPlay->TabStop = false;
			this->btnPlay->Click += gcnew System::EventHandler(this, &Form1::btnPlay_Click);
			// 
			// btnRecord
			// 
			this->btnRecord->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnRecord.Image")));
			this->btnRecord->Location = System::Drawing::Point(345, 28);
			this->btnRecord->Name = L"btnRecord";
			this->btnRecord->Size = System::Drawing::Size(68, 50);
			this->btnRecord->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->btnRecord->TabIndex = 0;
			this->btnRecord->TabStop = false;
			this->btnRecord->Click += gcnew System::EventHandler(this, &Form1::btnRecord_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 58);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(347, 89);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->Location = System::Drawing::Point(12, 153);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(549, 77);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox4.BackgroundImage")));
			this->pictureBox4->Location = System::Drawing::Point(12, 236);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(262, 68);
			this->pictureBox4->TabIndex = 6;
			this->pictureBox4->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->btnPlay);
			this->panel1->Controls->Add(this->btnRecord);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 568);
			this->panel1->Name = L"panel1";
			this->panel1->Padding = System::Windows::Forms::Padding(10);
			this->panel1->Size = System::Drawing::Size(953, 118);
			this->panel1->TabIndex = 7;
			this->panel1->Tag = L"";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::Snow;
			this->button1->Location = System::Drawing::Point(691, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(172, 50);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Live Training";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::DarkBlue;
			this->label2->Location = System::Drawing::Point(360, 81);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(121, 27);
			this->label2->TabIndex = 8;
			this->label2->Text = L"REC/PLAY";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(1, 12);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(100, 66);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox3->TabIndex = 8;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &Form1::pictureBox3_Click);
			// 
			// vocab
			// 
			this->vocab->BackColor = System::Drawing::Color::DarkGoldenrod;
			this->vocab->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->vocab->ForeColor = System::Drawing::Color::Snow;
			this->vocab->Location = System::Drawing::Point(691, 435);
			this->vocab->Name = L"vocab";
			this->vocab->Size = System::Drawing::Size(172, 50);
			this->vocab->TabIndex = 10;
			this->vocab->Text = L"Vocabulary";
			this->vocab->UseVisualStyleBackColor = false;
			this->vocab->Click += gcnew System::EventHandler(this, &Form1::vocab_Click);
			// 
			// About
			// 
			this->About->BackColor = System::Drawing::Color::Maroon;
			this->About->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->About->ForeColor = System::Drawing::Color::Snow;
			this->About->Location = System::Drawing::Point(691, 358);
			this->About->Name = L"About";
			this->About->Size = System::Drawing::Size(172, 50);
			this->About->TabIndex = 11;
			this->About->Text = L"About";
			this->About->UseVisualStyleBackColor = false;
			this->About->Click += gcnew System::EventHandler(this, &Form1::About_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::ForestGreen;
			this->button2->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::Snow;
			this->button2->Location = System::Drawing::Point(691, 513);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(172, 50);
			this->button2->TabIndex = 12;
			this->button2->Text = L"Live Models";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// modelLabel
			// 
			this->modelLabel->BackColor = System::Drawing::Color::Transparent;
			this->modelLabel->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->modelLabel->ForeColor = System::Drawing::Color::Red;
			this->modelLabel->Location = System::Drawing::Point(13, 358);
			this->modelLabel->Name = L"modelLabel";
			this->modelLabel->Size = System::Drawing::Size(548, 33);
			this->modelLabel->TabIndex = 13;
			this->modelLabel->Text = L"Model";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(953, 686);
			this->Controls->Add(this->modelLabel);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->About);
			this->Controls->Add(this->vocab);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Font = (gcnew System::Drawing::Font(L"MV Boli", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Limo";
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->VisibleChanged += gcnew System::EventHandler(this, &Form1::Form1_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->btnPlay))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->btnRecord))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	/*private: System::Void btnPlay_Click(System::Object^  sender, System::EventArgs^  e) {
				 	//this->Cursor = L"WaitCursor";
				 this->Text = "recording ...";
				 this->Enabled = false;
				 btnPlay->Enabled = false;
				 btnRecord->Enabled = false;
				 PlayRecord();
				 this->Enabled = true;
				 btnPlay->Enabled = true;
				 btnRecord->Enabled = true;
				 this->Text = "Limo";
				// this->cursor = L"Default";

			 }*/
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				
				// this->Enabled = false;
				FILE *fw = fopen("selected_model.txt","w");
				fprintf(fw,"%s","default");
				fclose(fw);
				//this->Enabled = false;
				btnPlay->Enabled = false;
				btnRecord->Enabled = false;
				modelLabel->Visible = false;
				timer1->Start();
				// this->Enabled = true;
				 //btnRecord->Enabled = true;
				 
				 
			 }
	/*private: System::Void btnRecord_Click(System::Object^  sender, System::EventArgs^  e) {
				
				// this->Cursor = L"WaitCursor";
				 this->Text = "recording ...";
				 this->Enabled = false;
				 btnPlay->Enabled = false;
				 btnRecord->Enabled = false;
				 StartRecord("audio.txt","audio.wav");
				 this->Enabled = true;
				 btnPlay->Enabled = true;
				 btnRecord->Enabled = true;
				 this->Text = "Limo";
				 Paths ^dat = gcnew Paths();
				 //System::String^ systemString = msclr::interop::marshal_as<System::String^>(stdString);
				 dat->setImagePath(msclr::interop::marshal_as<System::String^>(imagePaths[3]));
				 dat->setAudioPath(msclr::interop::marshal_as<System::String^>(audioPaths[1]));
				 dat->setDescription(msclr::interop::marshal_as<System::String^>(descriptions[3]));
				 Form2^ form2 = gcnew Form2(this,dat);
				 form2->Show();
				 this->Hide();
				// this->cursor = L"Default";


			 }*/
	private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				
			 }


private: System::Void btnRecord_Click(System::Object^  sender, System::EventArgs^  e) {
			 // this->Cursor = L"WaitCursor";
			 
				 //this->Text = "recording ...";
				 //lblMsg->Text = "RECORDING...";
				//this->Enabled = false;
				btnPlay->Enabled = false;
				btnRecord->Enabled = false;
					Form3^ f3 = gcnew Form3();
				f3->Show();
				 StartRecord("audio.txt","audio.wav");
				 f3->Close();
				 //lblMsg->Text = "PLAYING...";
				 //PlayRecord();
				 PlaySound(TEXT("audio.wav"),NULL,SND_FILENAME);
				 //lblMsg->Text = "";
				 if(btnPlay->Enabled == false)
					btnPlay->Enabled = true;
				 //this->Enabled = true;
				 
				 //this->Text = "Limo";
				 Paths ^dat = gcnew Paths();
				 //System::String^ systemString = msclr::interop::marshal_as<System::String^>(stdString);
				 /*if(index == 10) index = 1;
				 else index++;*/
				 FILE *fp = fopen("selected_model.txt","r");
				 char text[100],file_name[200];
				 fscanf(fp,"%s",text);
				 fclose(fp);
				 strcpy(file_name,"live_models/");
				 strcat(file_name,text);
				 index = test("audio.txt",file_name);//Index in model's vocab	 
				 /*char s[10];
				 sprintf(s,"%d",index);
				 MessageBox::Show(msclr::interop::marshal_as<System::String^>(s));*/
				 if(index != 0)
				 {
				 if(strcmp(text,"default")!=0){
				 strcat(file_name,"/vocab.txt");
				 fp = fopen(file_name,"r");
				 int indx=1;
				 while(fscanf(fp,"%s",file_name)==1 && indx++ != index);//word corresponding to the index
				 fclose(fp);
				 }
				 if(strcmp(text,"default")==0 || (index = searchAnimals(file_name))!=-1)//checking whether it is present in default dictionary
				 {
					 dat->setName(msclr::interop::marshal_as<System::String^>(animal_names[index]));
					 dat->setImagePath(msclr::interop::marshal_as<System::String^>(imagePaths[index]));
					 dat->setAudioPath(msclr::interop::marshal_as<System::String^>(audioPaths[index]));
					 dat->setDescription(msclr::interop::marshal_as<System::String^>(descriptions[index]));
					 dat->setAnimalSounds(msclr::interop::marshal_as<System::String^>(animalsounds[index]));
					 Form2^ form2 = gcnew Form2(this,dat);
					 form2->Show();
					 this->Hide();
				 }
				 else 
				{
					MessageBox::Show("Recognized word : " + msclr::interop::marshal_as<System::String^>(file_name),"Word Recognition",MessageBoxButtons::OK,MessageBoxIcon::Information);
				}
				 }
				 else
				 {
					//this->Enabled = false;
					error_flag = true;
					timer1->Start();
				 }
				// this->cursor = L"Default";
				 btnPlay->Enabled = true;
				 btnRecord->Enabled = true;
		 }
private: System::Void btnPlay_Click(System::Object^  sender, System::EventArgs^  e) {
			 //this->Cursor = L"WaitCursor";
				 //this->Text = "playing ...";
				 //this->Enabled = false;
				 btnPlay->Enabled = false;
				 btnRecord->Enabled = false;
				 PlaySound(TEXT("audio.wav"),NULL,SND_FILENAME);
				 //this->Enabled = true;
				 btnPlay->Enabled = true;
				 btnRecord->Enabled = true;
				 //this->Text = "Limo";
				// this->cursor = L"Default";
		 }

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 interval++;
			 if(interval >= 1)
			 {
				 //this->Text = L"Limo Speaking...";
				 if(error_flag == false)
				  PlaySound(TEXT("greeting.wav"),NULL,SND_FILENAME);
				 else
				 {
					 PlaySound(TEXT("error.wav"),NULL,SND_FILENAME);
					 error_flag = false;
				 }
				 // this->Text = L"Limo";
				 btnRecord->Enabled = true;
				// this->Enabled = true;
				 interval = 0;
				 timer1->Stop();
			 }
			 

		 }

private: System::Void pictureBox3_Click(System::Object^  sender, System::EventArgs^  e) {
			// this->Text = L"Limo Speaking...";	
			// this->Enabled = false;
			     btnPlay->Enabled = false;
				 btnRecord->Enabled = false;
				 PlaySound(TEXT("greeting.wav"),NULL,SND_FILENAME);
				 btnPlay->Enabled = true;
				 btnRecord->Enabled = true;
				 // this->Text = L"Limo";
				//this->Enabled = true;
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 InputForm1^ inpf = gcnew InputForm1(this);
			 inpf->Show();
			 this->Hide();
		 }
private: System::Void About_Click(System::Object^  sender, System::EventArgs^  e) {
			 AboutForm^ about = gcnew AboutForm(this);
			 about->Show();
			 this->Hide();
		 }
private: System::Void vocab_Click(System::Object^  sender, System::EventArgs^  e) {
			 FILE *fp = fopen("selected_model.txt","r");
			 char text[100];
			 fscanf(fp,"%s",text);
			 fclose(fp);
			 if(strcmp(text,"default")==0)
			 {
			 DictionaryForm^ vocab = gcnew DictionaryForm(this);
			 vocab->Show();
			 }
			 else
			 {
				  DictionaryForm1^ vocab = gcnew DictionaryForm1(this);
				vocab->Show();
			 }
			 this->Hide();
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 LiveModelForm^ live_models = gcnew LiveModelForm(this);
			 live_models->Show();
			 this->Hide();
				 
		 }
private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
			
			 //MessageBox::Show(modelLabel->Text);
		 }
private: System::Void Form1_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			  FILE *fp = fopen("selected_model.txt","r");
			 char text[100];
			 fscanf(fp,"%s",text);
			 fclose(fp);
			 if(strcmp(text,"default")==0)
			 {
				 modelLabel->Visible = false;
				 modelLabel->Text = "";
			 }
			 else{
				 modelLabel->Visible = true;
				 modelLabel->Text = "Current Model : "+gcnew String(text);
				 
			 }
		 }
};
}

