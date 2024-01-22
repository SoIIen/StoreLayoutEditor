#pragma once

#include "GraphicEditor.h"

namespace StoreLayoutEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Ñâîäêà äëÿ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: äîáàâüòå êîä êîíñòğóêòîğà
			//
		}

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ğåñóğñû.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuLayoutFile;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuClearLayout;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuLoadLayout;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuSaveLayout;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::ToolStripMenuItem^ ToolStripMenuExitProgram;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::ToolStripMenuItem^ AddWallToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddHorizontalWallToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddVerticalWallToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddSectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddMilkSectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddMeatSectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddFishSectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddBakerySectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddGrocerySectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AddVegetableSectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ CashRegisterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ äîáàâèòüÍàïğàâëåíèåToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ââåğõToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ âíèçToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ âëåâîToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ âïğàâîToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::PictureBox^ pictureBox6;
	private: System::Windows::Forms::PictureBox^ pictureBox7;
	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::PictureBox^ pictureBox13;
	private: System::Windows::Forms::PictureBox^ pictureBox11;
	private: System::Windows::Forms::PictureBox^ pictureBox12;
	private: System::Windows::Forms::PictureBox^ pictureBox9;
	private: System::Windows::Forms::PictureBox^ pictureBox10;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::ToolStripMenuItem^ xMLÔàéëToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ èçîáğàæåíèåToolStripMenuItem;

	protected:

	private:
		Primitive::GraphicElementContainer^ graphicElements = gcnew Primitive::GraphicElementContainer();

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->AddWallToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddHorizontalWallToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddVerticalWallToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CashRegisterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddGrocerySectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddMeatSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddMilkSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddVegetableSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddFishSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddBakerySectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->äîáàâèòüÍàïğàâëåíèåToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ââåğõToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âíèçToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âëåâîToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âïğàâîToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuClearLayout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuLayoutFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuLoadLayout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuSaveLayout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xMLÔàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->èçîáğàæåíèåToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuExitProgram = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->AddWallToolStripMenuItem,
					this->AddSectionToolStripMenuItem, this->äîáàâèòüÍàïğàâëåíèåToolStripMenuItem, this->toolStripMenuClearLayout, this->toolStripMenuLayoutFile,
					this->ToolStripMenuExitProgram
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(857, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// AddWallToolStripMenuItem
			// 
			this->AddWallToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->AddHorizontalWallToolStripMenuItem,
					this->AddVerticalWallToolStripMenuItem
			});
			this->AddWallToolStripMenuItem->Name = L"AddWallToolStripMenuItem";
			this->AddWallToolStripMenuItem->Size = System::Drawing::Size(104, 20);
			this->AddWallToolStripMenuItem->Text = L"Äîáàâèòü ñòåíó";
			// 
			// AddHorizontalWallToolStripMenuItem
			// 
			this->AddHorizontalWallToolStripMenuItem->Name = L"AddHorizontalWallToolStripMenuItem";
			this->AddHorizontalWallToolStripMenuItem->Size = System::Drawing::Size(196, 22);
			this->AddHorizontalWallToolStripMenuItem->Text = L"Ãîğèçîíòàëüíàÿ ñòåíà";
			this->AddHorizontalWallToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddHorizontalWall);
			// 
			// AddVerticalWallToolStripMenuItem
			// 
			this->AddVerticalWallToolStripMenuItem->Name = L"AddVerticalWallToolStripMenuItem";
			this->AddVerticalWallToolStripMenuItem->Size = System::Drawing::Size(196, 22);
			this->AddVerticalWallToolStripMenuItem->Text = L"Âåğòèêàëüíàÿ ñòåíà";
			this->AddVerticalWallToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddVerticalWall);
			// 
			// AddSectionToolStripMenuItem
			// 
			this->AddSectionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->CashRegisterToolStripMenuItem,
					this->AddGrocerySectionToolStripMenuItem, this->AddMeatSectionToolStripMenuItem, this->AddMilkSectionToolStripMenuItem, this->AddVegetableSectionToolStripMenuItem,
					this->AddFishSectionToolStripMenuItem, this->AddBakerySectionToolStripMenuItem
			});
			this->AddSectionToolStripMenuItem->Name = L"AddSectionToolStripMenuItem";
			this->AddSectionToolStripMenuItem->Size = System::Drawing::Size(105, 20);
			this->AddSectionToolStripMenuItem->Text = L"Äîáàâèòü îòäåë";
			// 
			// CashRegisterToolStripMenuItem
			// 
			this->CashRegisterToolStripMenuItem->Name = L"CashRegisterToolStripMenuItem";
			this->CashRegisterToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->CashRegisterToolStripMenuItem->Text = L"Êàññîâàÿ çîíà";
			this->CashRegisterToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddCashRegistereSection);
			// 
			// AddGrocerySectionToolStripMenuItem
			// 
			this->AddGrocerySectionToolStripMenuItem->Name = L"AddGrocerySectionToolStripMenuItem";
			this->AddGrocerySectionToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->AddGrocerySectionToolStripMenuItem->Text = L"Áàêàëåéíûé";
			this->AddGrocerySectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddGrocerySection);
			// 
			// AddMeatSectionToolStripMenuItem
			// 
			this->AddMeatSectionToolStripMenuItem->Name = L"AddMeatSectionToolStripMenuItem";
			this->AddMeatSectionToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->AddMeatSectionToolStripMenuItem->Text = L"Êîëáàñíî-ìÿñíîé";
			this->AddMeatSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddMeatSection);
			// 
			// AddMilkSectionToolStripMenuItem
			// 
			this->AddMilkSectionToolStripMenuItem->Name = L"AddMilkSectionToolStripMenuItem";
			this->AddMilkSectionToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->AddMilkSectionToolStripMenuItem->Text = L"Ìîëî÷íûé";
			this->AddMilkSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddMilkSection);
			// 
			// AddVegetableSectionToolStripMenuItem
			// 
			this->AddVegetableSectionToolStripMenuItem->Name = L"AddVegetableSectionToolStripMenuItem";
			this->AddVegetableSectionToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->AddVegetableSectionToolStripMenuItem->Text = L"Îâîùíîé";
			this->AddVegetableSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddVegetableSection);
			// 
			// AddFishSectionToolStripMenuItem
			// 
			this->AddFishSectionToolStripMenuItem->Name = L"AddFishSectionToolStripMenuItem";
			this->AddFishSectionToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->AddFishSectionToolStripMenuItem->Text = L"Ğûáíûé";
			this->AddFishSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddFishSection);
			// 
			// AddBakerySectionToolStripMenuItem
			// 
			this->AddBakerySectionToolStripMenuItem->Name = L"AddBakerySectionToolStripMenuItem";
			this->AddBakerySectionToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->AddBakerySectionToolStripMenuItem->Text = L"Õëåáîáóëî÷íûé";
			this->AddBakerySectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddBakerySection);
			// 
			// äîáàâèòüÍàïğàâëåíèåToolStripMenuItem
			// 
			this->äîáàâèòüÍàïğàâëåíèåToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ââåğõToolStripMenuItem,
					this->âíèçToolStripMenuItem, this->âëåâîToolStripMenuItem, this->âïğàâîToolStripMenuItem
			});
			this->äîáàâèòüÍàïğàâëåíèåToolStripMenuItem->Name = L"äîáàâèòüÍàïğàâëåíèåToolStripMenuItem";
			this->äîáàâèòüÍàïğàâëåíèåToolStripMenuItem->Size = System::Drawing::Size(146, 20);
			this->äîáàâèòüÍàïğàâëåíèåToolStripMenuItem->Text = L"Äîáàâèòü íàïğàâëåíèå";
			// 
			// ââåğõToolStripMenuItem
			// 
			this->ââåğõToolStripMenuItem->Name = L"ââåğõToolStripMenuItem";
			this->ââåğõToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->ââåğõToolStripMenuItem->Text = L"Ââåğõ";
			this->ââåğõToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddArrowUp);
			// 
			// âíèçToolStripMenuItem
			// 
			this->âíèçToolStripMenuItem->Name = L"âíèçToolStripMenuItem";
			this->âíèçToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->âíèçToolStripMenuItem->Text = L"Âíèç";
			this->âíèçToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddArrowDown);
			// 
			// âëåâîToolStripMenuItem
			// 
			this->âëåâîToolStripMenuItem->Name = L"âëåâîToolStripMenuItem";
			this->âëåâîToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->âëåâîToolStripMenuItem->Text = L"Âëåâî";
			this->âëåâîToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddArrowLeft);
			// 
			// âïğàâîToolStripMenuItem
			// 
			this->âïğàâîToolStripMenuItem->Name = L"âïğàâîToolStripMenuItem";
			this->âïğàâîToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->âïğàâîToolStripMenuItem->Text = L"Âïğàâî";
			this->âïğàâîToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddArrowRight);
			// 
			// toolStripMenuClearLayout
			// 
			this->toolStripMenuClearLayout->Name = L"toolStripMenuClearLayout";
			this->toolStripMenuClearLayout->Size = System::Drawing::Size(71, 20);
			this->toolStripMenuClearLayout->Text = L"Î÷èñòèòü";
			this->toolStripMenuClearLayout->Click += gcnew System::EventHandler(this, &MyForm::Click_LayoutClear);
			// 
			// toolStripMenuLayoutFile
			// 
			this->toolStripMenuLayoutFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuLoadLayout,
					this->toolStripMenuSaveLayout
			});
			this->toolStripMenuLayoutFile->Name = L"toolStripMenuLayoutFile";
			this->toolStripMenuLayoutFile->Size = System::Drawing::Size(48, 20);
			this->toolStripMenuLayoutFile->Text = L"Ôàéë";
			// 
			// toolStripMenuLoadLayout
			// 
			this->toolStripMenuLoadLayout->Name = L"toolStripMenuLoadLayout";
			this->toolStripMenuLoadLayout->Size = System::Drawing::Size(163, 22);
			this->toolStripMenuLoadLayout->Text = L"Çàãğóçèòü";
			this->toolStripMenuLoadLayout->Click += gcnew System::EventHandler(this, &MyForm::Click_LoadLayout);
			// 
			// toolStripMenuSaveLayout
			// 
			this->toolStripMenuSaveLayout->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->xMLÔàéëToolStripMenuItem,
					this->èçîáğàæåíèåToolStripMenuItem
			});
			this->toolStripMenuSaveLayout->Name = L"toolStripMenuSaveLayout";
			this->toolStripMenuSaveLayout->Size = System::Drawing::Size(163, 22);
			this->toolStripMenuSaveLayout->Text = L"Ñîõğàíèòü êàê...";
			// 
			// xMLÔàéëToolStripMenuItem
			// 
			this->xMLÔàéëToolStripMenuItem->Name = L"xMLÔàéëToolStripMenuItem";
			this->xMLÔàéëToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->xMLÔàéëToolStripMenuItem->Text = L"XML";
			this->xMLÔàéëToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_SaveLayoutXML);
			// 
			// èçîáğàæåíèåToolStripMenuItem
			// 
			this->èçîáğàæåíèåToolStripMenuItem->Name = L"èçîáğàæåíèåToolStripMenuItem";
			this->èçîáğàæåíèåToolStripMenuItem->Size = System::Drawing::Size(150, 22);
			this->èçîáğàæåíèåToolStripMenuItem->Text = L"Èçîáğàæåíèå";
			this->èçîáğàæåíèåToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_SaveLayoutImage);
			// 
			// ToolStripMenuExitProgram
			// 
			this->ToolStripMenuExitProgram->Name = L"ToolStripMenuExitProgram";
			this->ToolStripMenuExitProgram->Size = System::Drawing::Size(138, 20);
			this->ToolStripMenuExitProgram->Text = L"Âûõîä èç ïğîãğàììû";
			this->ToolStripMenuExitProgram->Click += gcnew System::EventHandler(this, &MyForm::Click_ExitProgram);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 17;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::Tick_UpdateLayout);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(833, 362);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->pictureBox9);
			this->groupBox1->Controls->Add(this->pictureBox10);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->pictureBox13);
			this->groupBox1->Controls->Add(this->pictureBox2);
			this->groupBox1->Controls->Add(this->pictureBox5);
			this->groupBox1->Controls->Add(this->pictureBox11);
			this->groupBox1->Controls->Add(this->pictureBox12);
			this->groupBox1->Controls->Add(this->pictureBox6);
			this->groupBox1->Controls->Add(this->pictureBox7);
			this->groupBox1->Controls->Add(this->pictureBox8);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->pictureBox4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->pictureBox3);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(12, 395);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(833, 62);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Îáîçíà÷åíèÿ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(611, 38);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(121, 13);
			this->label8->TabIndex = 10;
			this->label8->Text = L"Äâèæåíèå ïîêóïàòåëÿ";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(611, 19);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(41, 13);
			this->label9->TabIndex = 11;
			this->label9->Text = L"Ïğî¸ì";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(546, 38);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(33, 13);
			this->label10->TabIndex = 12;
			this->label10->Text = L"Îêíî";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(546, 19);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(40, 13);
			this->label11->TabIndex = 13;
			this->label11->Text = L"Äâåğü";
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackColor = System::Drawing::Color::Black;
			this->pictureBox9->Location = System::Drawing::Point(592, 38);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(13, 13);
			this->pictureBox9->TabIndex = 6;
			this->pictureBox9->TabStop = false;
			// 
			// pictureBox10
			// 
			this->pictureBox10->BackColor = System::Drawing::Color::LightGray;
			this->pictureBox10->Location = System::Drawing::Point(592, 19);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(13, 13);
			this->pictureBox10->TabIndex = 7;
			this->pictureBox10->TabStop = false;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(438, 38);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(37, 13);
			this->label12->TabIndex = 14;
			this->label12->Text = L"Ñòåíà";
			// 
			// pictureBox13
			// 
			this->pictureBox13->BackColor = System::Drawing::Color::Gray;
			this->pictureBox13->Location = System::Drawing::Point(419, 38);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(13, 13);
			this->pictureBox13->TabIndex = 10;
			this->pictureBox13->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Purple;
			this->pictureBox2->Location = System::Drawing::Point(6, 19);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(13, 13);
			this->pictureBox2->TabIndex = 5;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::Color::Gold;
			this->pictureBox5->Location = System::Drawing::Point(419, 19);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(13, 13);
			this->pictureBox5->TabIndex = 5;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox11
			// 
			this->pictureBox11->BackColor = System::Drawing::Color::LightSkyBlue;
			this->pictureBox11->Location = System::Drawing::Point(527, 38);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(13, 13);
			this->pictureBox11->TabIndex = 8;
			this->pictureBox11->TabStop = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->BackColor = System::Drawing::Color::DarkRed;
			this->pictureBox12->Location = System::Drawing::Point(527, 19);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(13, 13);
			this->pictureBox12->TabIndex = 9;
			this->pictureBox12->TabStop = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::Color::Cyan;
			this->pictureBox6->Location = System::Drawing::Point(276, 38);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(13, 13);
			this->pictureBox6->TabIndex = 6;
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::Orange;
			this->pictureBox7->Location = System::Drawing::Point(276, 19);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(13, 13);
			this->pictureBox7->TabIndex = 7;
			this->pictureBox7->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::Color::Teal;
			this->pictureBox8->Location = System::Drawing::Point(160, 38);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(13, 13);
			this->pictureBox8->TabIndex = 8;
			this->pictureBox8->TabStop = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(438, 19);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(83, 13);
			this->label7->TabIndex = 9;
			this->label7->Text = L"Êàññîâàÿ çîíà";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(295, 38);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(80, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Ğûáíûé îòäåë";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(295, 19);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(118, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"Õëåáîáóëî÷íûé îòäåë";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(179, 38);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(86, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Îâîùíîé îòäåë";
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::AntiqueWhite;
			this->pictureBox4->Location = System::Drawing::Point(160, 19);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(13, 13);
			this->pictureBox4->TabIndex = 4;
			this->pictureBox4->TabStop = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(179, 19);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Ìîëî÷íûé îòäåë";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(25, 38);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(129, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Êîëáàñíî-ìÿñíîé îòäåë";
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Crimson;
			this->pictureBox3->Location = System::Drawing::Point(6, 38);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(13, 13);
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(25, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(102, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Áàêàëåéíûé îòäåë";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(857, 469);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->DoubleBuffered = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"Ïëàíèğîâùèê ìàãàçèíà";
			this->MouseHover += gcnew System::EventHandler(this, &MyForm::onMouseHover);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void onMouseHover(System::Object^ sender, System::EventArgs^ e) {
	this->menuStrip1->Focus();
}
private: System::Void Click_LayoutClear(System::Object^ sender, System::EventArgs^ e) {
	this->graphicElements->emptyGraphicElements();
}
private: System::Void Click_LoadLayout(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
	openFileDialog->Filter = "XML files (*.xml)|*.xml";

	if (openFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
		XmlReader^ reader = XmlReader::Create(openFileDialog->FileName);
		try {
			graphicElements->emptyGraphicElements();
			graphicElements->deserialize(reader, this->pictureBox1->Controls);
			
		}
		finally {
			reader->Close();
		}
	}
}
private: System::Void Click_SaveLayoutXML(System::Object^ sender, System::EventArgs^ e) {
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
	saveFileDialog->Filter = "XML files (*.xml)|*.xml";

	if (saveFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
		
		XmlWriter^ writer = XmlWriter::Create(saveFileDialog->FileName);
		try {
			graphicElements->serialize(writer);
		}
		finally {
			writer->Flush();
			writer->Close();
		}
	}
}
private: System::Void Click_ExitProgram(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit();
}
private: System::Void Tick_UpdateLayout(System::Object^ sender, System::EventArgs^ e) {
	this->PerformLayout();
	this->graphicElements->updateGraphic();
	this->Invalidate();
}
private: System::Void Click_AddGrocerySection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Purple, 100, 100);
	this->pictureBox1->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddMilkSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::AntiqueWhite, 100, 100);
	this->pictureBox1->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddMeatSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Crimson, 100, 100);
	this->pictureBox1->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddFishSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Cyan, 100, 100);
	this->pictureBox1->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddBakerySection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Orange, 100, 100);
	this->pictureBox1->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddVegetableSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Teal, 100, 100);
	this->pictureBox1->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddCashRegistereSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Gold, 100, 100);
	this->pictureBox1->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddVerticalWall(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Wall^ newWall = gcnew GraphicObject::Wall(System::Drawing::Color::Gray, Support::Orientation::Vertical, 15, 50);
	this->pictureBox1->Controls->Add(newWall);
	this->graphicElements->addElement(newWall);
	newWall->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddHorizontalWall(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Wall^ newWall = gcnew GraphicObject::Wall(System::Drawing::Color::Gray, Support::Orientation::Horizontal, 50, 15);
	this->pictureBox1->Controls->Add(newWall);
	this->graphicElements->addElement(newWall);
	newWall->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddArrowUp(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Arrow^ newArrow = gcnew GraphicObject::Arrow(Support::Direction::Up);
	this->pictureBox1->Controls->Add(newArrow);
	this->pictureBox1->Controls->SetChildIndex(newArrow, this->pictureBox1->Controls->Count - 1);
	this->graphicElements->addElement(newArrow);
	newArrow->Location = Drawing::Point(50, 50);
	newArrow->BringToFront();
}
private: System::Void Click_AddArrowDown(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Arrow^ newArrow = gcnew GraphicObject::Arrow(Support::Direction::Down);
	this->pictureBox1->Controls->Add(newArrow);
	this->pictureBox1->Controls->SetChildIndex(newArrow, this->pictureBox1->Controls->Count - 1);
	this->graphicElements->addElement(newArrow);
	newArrow->Location = Drawing::Point(50, 50);
	newArrow->BringToFront();
}
private: System::Void Click_AddArrowLeft(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Arrow^ newArrow = gcnew GraphicObject::Arrow(Support::Direction::Left);
	this->pictureBox1->Controls->Add(newArrow);
	this->pictureBox1->Controls->SetChildIndex(newArrow, this->pictureBox1->Controls->Count - 1);
	this->graphicElements->addElement(newArrow);
	newArrow->Location = Drawing::Point(50, 50);
	newArrow->BringToFront();
}
private: System::Void Click_AddArrowRight(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Arrow^ newArrow = gcnew GraphicObject::Arrow(Support::Direction::Right);
	this->pictureBox1->Controls->Add(newArrow);
	this->pictureBox1->Controls->SetChildIndex(newArrow, this->pictureBox1->Controls->Count - 1);
	this->graphicElements->addElement(newArrow);
	newArrow->Location = Drawing::Point(50, 50);
	newArrow->BringToFront();
}
private: System::Void Click_SaveLayoutImage(System::Object^ sender, System::EventArgs^ e) {
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
	saveFileDialog->Filter = "Image files (*.bmp)|*.bmp";

	if (saveFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
		for each (Control ^ control in this->pictureBox1->Controls) {
			if (control->GetType() == GraphicObject::Arrow::typeid) {
				this->pictureBox1->Controls->SetChildIndex(control, this->pictureBox1->Controls->Count - 1);
			}
		}
		Bitmap^ bmp = gcnew Bitmap(this->pictureBox1->Width, this->pictureBox1->Height);
		this->pictureBox1->DrawToBitmap(bmp, this->pictureBox1->ClientRectangle);
		bmp->Save(saveFileDialog->FileName, Imaging::ImageFormat::Bmp);
		delete bmp;
		for each (Control ^ control in this->pictureBox1->Controls) {
			if (control->GetType() == GraphicObject::Arrow::typeid) {
				control->BringToFront();
			}
		}
	}
}
};
}