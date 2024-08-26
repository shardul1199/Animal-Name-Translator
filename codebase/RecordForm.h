
#pragma once
//#include "MyAudioRecorder.h"

#include <Windows.h>
#include <fstream>
#include <iostream>
//#include <vector>
//#include "model.h"
#include <msclr\marshal_cppstd.h>





//#include<stdio.h>
//#include<stdlib.h>

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

#include <stdint.h>
#include"Form3.h"

#include"UserData.h"

#define seconds 3
#define sample_rate 16000
#define channel 1
#define bits_per_sample 16
typedef struct WAV_HEADER {
  /* RIFF Chunk Descriptor */
  uint8_t RIFF[4] ; // RIFF Header Magic header
  uint32_t ChunkSize;                     // RIFF Chunk Size
  uint8_t WAVE[4]; // WAVE Header
  /* "fmt" sub-chunk */
  uint8_t fmt[4]; // FMT header
  uint32_t Subchunk1Size;           // Size of the fmt chunk
  uint16_t AudioFormat; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
                            // Mu-Law, 258=IBM A-Law, 259=ADPCM
  uint16_t NumOfChan;   // Number of channels 1=Mono 2=Sterio
  uint32_t SamplesPerSec;   // Sampling Frequency in Hz
  uint32_t bytesPerSec; // bytes per second
  uint16_t blockAlign;          // 2=16-bit mono, 4=16-bit stereo
  uint16_t bitsPerSample;      // Number of bits per sample
  /* "data" sub-chunk */
  uint8_t Subchunk2ID[4]; // "data"  string
  uint32_t Subchunk2Size;                        // Sampled data length
} wav_hdr;
namespace Speech_Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RecordForm
	/// </summary>
	public ref class RecordForm : public System::Windows::Forms::Form
	{
	private:
		Form^ parent;
		userData^ udat;
		String^ prefix;
		char *StringToChar(System::String^ orig)
	{
		pin_ptr<const wchar_t> wch = PtrToStringChars(orig);

    // Make a copy of the System::String as a multibyte
    // char* string. Allocate two bytes in the multibyte
    // output string for every wide character in the input
    // string, including space for a terminating null.
    size_t origsize = wcslen(wch) + 1;
    const size_t newsize = origsize * 2;
    size_t convertedChars = 0;
    char* nstring = new char[newsize];
    wcstombs_s(&convertedChars, nstring, newsize, wch, _TRUNCATE);
	return nstring;
	}
	void writeWAV(std::string binfile,std::string wavfile)
{
	//Structure to initialize headers for .wav file 

	wav_hdr hdr;
	hdr.RIFF[0] = 'R';
	hdr.RIFF[1] = 'I';
	hdr.RIFF[2] = 'F';
	hdr.RIFF[3] = 'F';
	hdr.WAVE[0] = 'W';
	hdr.WAVE[1] = 'A';
	hdr.WAVE[2] = 'V';
	hdr.WAVE[3] = 'E';
	hdr.fmt[0] = 'f';
	hdr.fmt[1] = 'm';
	hdr.fmt[2] = 't';
	hdr.fmt[3] = ' ';
	hdr.Subchunk1Size = 16;
	hdr.AudioFormat = 1;
	hdr.NumOfChan = channel;
	hdr.SamplesPerSec = sample_rate;
	hdr.bitsPerSample = bits_per_sample;
	hdr.bytesPerSec = sample_rate*channel*bits_per_sample/2;
	hdr.blockAlign = channel*bits_per_sample/8;
	
	hdr.Subchunk2ID[0] = 'd';
	hdr.Subchunk2ID[1] = 'a';
	hdr.Subchunk2ID[2] = 't';
	hdr.Subchunk2ID[3] = 'a';
	
	
	static_assert(sizeof(wav_hdr) == 44, "");

   std::ifstream in(binfile, std::ifstream::binary);

  uint32_t fsize = in.tellg();
  in.seekg(0, std::ios::end);
  fsize = (uint32_t)in.tellg() - fsize;
  in.seekg(0, std::ios::beg);

  printf("file size: %u\n", fsize);

  hdr.ChunkSize = fsize + sizeof(wav_hdr)  - 8;
  hdr.Subchunk2Size = fsize + sizeof(wav_hdr) - 44;

    std::ofstream out(wavfile, std::ios::binary);
  out.write(reinterpret_cast<const char *>(&hdr), sizeof(hdr));

  int16_t d;
  for (int i = 0; i < fsize; ++i) {
    // TODO: read/write in blocks
    in.read(reinterpret_cast<char *>(&d), sizeof(int16_t));
    out.write(reinterpret_cast<char *>(&d), sizeof(int16_t));
  }


}

void StartRecord(std:: string textfile,std::string wavfile)
{
	short int waveIn[sample_rate*seconds];
	 //buffer to store audio samples

const int NUMPTS = sample_rate * seconds;   // 3 seconds
int sampleRate = sample_rate;  
// 'short int' is a 16-bit type; I request 16-bit samples below
                         // for 8-bit capture, you'd use 'unsigned char' or 'BYTE' 8-bit     type
 HWAVEIN      hWaveIn;
 MMRESULT result;

 WAVEFORMATEX pFormat;
 pFormat.wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
 pFormat.nChannels=channel;                    //  1=mono, 2=stereo
 pFormat.nSamplesPerSec=sampleRate; // 16000
 pFormat.wBitsPerSample=bits_per_sample; //  16 for high quality, 8 for telephone-grade
 pFormat.nAvgBytesPerSec=sampleRate*channel*bits_per_sample/8;   // = nSamplesPerSec * n.Channels *    wBitsPerSample/8
 pFormat.nBlockAlign=channel*bits_per_sample/8;                  // = n.Channels * wBitsPerSample/8
 pFormat.cbSize=0;

 // Specify recording parameters

 result = waveInOpen(&hWaveIn, WAVE_MAPPER,&pFormat,
        0L, 0L, WAVE_FORMAT_DIRECT);

  WAVEHDR      WaveInHdr;
 // Set up and prepare header for input
  WaveInHdr.lpData = (LPSTR)waveIn;
  WaveInHdr.dwBufferLength = NUMPTS*2;
  WaveInHdr.dwBytesRecorded=0;
  WaveInHdr.dwUser = 0L;
  WaveInHdr.dwFlags = 0L;
  WaveInHdr.dwLoops = 0L;
  waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

 // Insert a wave input buffer
  result = waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));


 // Commence sampling input
  result = waveInStart(hWaveIn);


 std::cout << "recording...\n";

  Sleep(seconds * 1000);
 // Wait until finished recording

 waveInClose(hWaveIn);
 
 std::ofstream fwtxt(textfile,std::ofstream::out);
 std::ofstream fwbin("audio.bin",std::ios::binary);
 //Writing to text file
 if(fwtxt.is_open())
 {
	 for(int i=0; i <NUMPTS; i++)
		 fwtxt << waveIn[i]<<"\n";
	 fwtxt.close();
 }
 else
	 std::cout << "Problem with opening file : audio.txt\n";
 //Writing to bin file for making .wav file
 if(fwbin.is_open())
 {
	 for(int i=0; i <NUMPTS; i++)
		 fwbin.write(reinterpret_cast<char *>(&waveIn[i]),sizeof(int16_t));
	 fwbin.close();
 }
 else
	 std::cout << "Problem with opening file : audio.bin\n";
  writeWAV("audio.bin",wavfile);
  remove("audio.bin");
}
/*
void PlayRecord()
{
	const int NUMPTS = sample_rate * seconds;   // 3 seconds
int sampleRate = sample_rate;  
// 'short int' is a 16-bit type; I request 16-bit samples below
                            // for 8-bit capture, you'd    use 'unsigned char' or 'BYTE' 8-bit types

HWAVEIN  hWaveIn;

WAVEFORMATEX pFormat;
pFormat.wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
 pFormat.nChannels=channel;                    //  1=mono, 2=stereo
 pFormat.nSamplesPerSec=sampleRate; // 16000
 pFormat.wBitsPerSample=bits_per_sample; //  16 for high quality, 8 for telephone-grade
 pFormat.nAvgBytesPerSec=sampleRate*channel*bits_per_sample/8;   // = nSamplesPerSec * n.Channels *    wBitsPerSample/8
 pFormat.nBlockAlign=channel*bits_per_sample/8;                  // = n.Channels * wBitsPerSample/8
 pFormat.cbSize=0;

// Specify recording parameters

waveInOpen(&hWaveIn, WAVE_MAPPER,&pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);

WAVEHDR      WaveInHdr;
// Set up and prepare header for input
WaveInHdr.lpData = (LPSTR)waveIn;
WaveInHdr.dwBufferLength = NUMPTS*2;
WaveInHdr.dwBytesRecorded=0;
WaveInHdr.dwUser = 0L;
WaveInHdr.dwFlags = 0L;
WaveInHdr.dwLoops = 0L;
waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));

HWAVEOUT hWaveOut;
std::cout << "playing...\n";
waveOutOpen(&hWaveOut, WAVE_MAPPER, &pFormat, 0, 0, WAVE_FORMAT_DIRECT);
waveOutWrite(hWaveOut, &WaveInHdr, sizeof(WaveInHdr)); // Playing the data
Sleep(seconds * 1000); //Sleep for as long as there was recorded

waveInClose(hWaveIn);
waveOutClose(hWaveOut);
}*/










	public:
		RecordForm(Form^ p,userData^ u)
		{
			parent =p;
			udat = u;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		
		RecordForm(void)
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
		~RecordForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected: 
	private: System::Windows::Forms::Button^  btnPlay;
	private: System::Windows::Forms::Button^  btnRecord;
	private: System::Windows::Forms::Button^  btnSubmit;
	private: System::Windows::Forms::Label^  lblRecord;

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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btnPlay = (gcnew System::Windows::Forms::Button());
			this->btnRecord = (gcnew System::Windows::Forms::Button());
			this->btnSubmit = (gcnew System::Windows::Forms::Button());
			this->lblRecord = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btnPlay);
			this->panel1->Controls->Add(this->btnRecord);
			this->panel1->Controls->Add(this->btnSubmit);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 108);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(520, 100);
			this->panel1->TabIndex = 0;
			// 
			// btnPlay
			// 
			this->btnPlay->BackColor = System::Drawing::Color::Yellow;
			this->btnPlay->Enabled = false;
			this->btnPlay->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnPlay->Location = System::Drawing::Point(186, 24);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(137, 64);
			this->btnPlay->TabIndex = 2;
			this->btnPlay->Text = L"PLAY";
			this->btnPlay->UseVisualStyleBackColor = false;
			this->btnPlay->Click += gcnew System::EventHandler(this, &RecordForm::btnPlay_Click);
			// 
			// btnRecord
			// 
			this->btnRecord->BackColor = System::Drawing::Color::Red;
			this->btnRecord->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnRecord->Location = System::Drawing::Point(31, 24);
			this->btnRecord->Name = L"btnRecord";
			this->btnRecord->Size = System::Drawing::Size(122, 64);
			this->btnRecord->TabIndex = 1;
			this->btnRecord->Text = L"REC";
			this->btnRecord->UseVisualStyleBackColor = false;
			this->btnRecord->Click += gcnew System::EventHandler(this, &RecordForm::btnRecord_Click);
			// 
			// btnSubmit
			// 
			this->btnSubmit->BackColor = System::Drawing::Color::Lime;
			this->btnSubmit->Enabled = false;
			this->btnSubmit->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnSubmit->ForeColor = System::Drawing::Color::Black;
			this->btnSubmit->Location = System::Drawing::Point(362, 24);
			this->btnSubmit->Name = L"btnSubmit";
			this->btnSubmit->Size = System::Drawing::Size(134, 64);
			this->btnSubmit->TabIndex = 0;
			this->btnSubmit->Text = L"CONFIRM";
			this->btnSubmit->UseVisualStyleBackColor = false;
			this->btnSubmit->Click += gcnew System::EventHandler(this, &RecordForm::btnSubmit_Click);
			// 
			// lblRecord
			// 
			this->lblRecord->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblRecord->Location = System::Drawing::Point(26, 28);
			this->lblRecord->Name = L"lblRecord";
			this->lblRecord->Size = System::Drawing::Size(470, 60);
			this->lblRecord->TabIndex = 1;
			this->lblRecord->Text = L"Recording \"cat\" utterance \"1\"";
			this->lblRecord->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// RecordForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->ClientSize = System::Drawing::Size(520, 208);
			this->Controls->Add(this->lblRecord);
			this->Controls->Add(this->panel1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"RecordForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"RecordForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &RecordForm::RecordForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &RecordForm::RecordForm_Load);
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void RecordForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 lblRecord->Text = L"Recording \""+udat->getWord()+"\" utterance \""+udat->getUtteranceIndex()+"\"";
				 prefix = "live_models/"+udat->getName()+"/"+udat->getWordIndex()+"/"+udat->getWordIndex()+"_"+udat->getUtteranceIndex();
			 }

			

		


private: System::Void btnRecord_Click(System::Object^  sender, System::EventArgs^  e) {
			 btnPlay->Enabled = false;
			 btnSubmit->Enabled = false;
			 btnRecord->Enabled = false;
			 char *audiotxt = StringToChar(prefix+".txt");
			 char *audiowav = StringToChar(prefix+".wav");
			 Form3^ f3 = gcnew Form3();
			 f3->Show();
			 StartRecord(audiotxt,audiowav);
			 f3->Close();
			 wchar_t wtext[100];
			mbstowcs(wtext, audiowav, strlen(audiowav)+1);//Plus null
			LPWSTR ptr = wtext;
			 PlaySound(ptr,NULL,SND_FILENAME);
			 btnPlay->Enabled = true;
			 btnSubmit->Enabled = true;
			 btnRecord->Enabled = true;
			 delete []audiotxt;
			 delete []audiowav;
			 
		 }
private: System::Void btnPlay_Click(System::Object^  sender, System::EventArgs^  e) {
			 btnPlay->Enabled = false;
			// btnSubmit->Enabled = false;
			 btnRecord->Enabled = false;
			 char *audiowav = StringToChar(prefix+".wav");
			  wchar_t wtext[100];
			mbstowcs(wtext, audiowav, strlen(audiowav)+1);//Plus null
			LPWSTR ptr = wtext;
			 PlaySound(ptr,NULL,SND_FILENAME);
			  delete []audiowav;
			 btnPlay->Enabled = true;
			 //btnSubmit->Enabled = true;
			 btnRecord->Enabled = true;
		 }
private: System::Void btnSubmit_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(MessageBox::Show("Are You Sure Want to Proceed ?","Record Data ",MessageBoxButtons::YesNo,MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
			 {
				parent->Show();
				this->Close();
			 }
			 else
			 {
					char *audiotxt = StringToChar(prefix+".txt");
					 char *audiowav = StringToChar(prefix+".wav");
					 remove(audiotxt);
					 remove(audiowav);
					 delete []audiotxt;
					 delete []audiowav;
					  btnSubmit->Enabled = false;
					  btnPlay->Enabled = false;
			 }
			 
		 }
private: System::Void RecordForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				parent->Show();	
		 }
};
}
