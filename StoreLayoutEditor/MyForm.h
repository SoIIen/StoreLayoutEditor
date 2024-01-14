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
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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
			this->AddGrocerySectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddMeatSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddMilkSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddVegetableSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddFishSectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddBakerySectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuClearLayout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuLayoutFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuLoadLayout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuSaveLayout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuExitProgram = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->AddWallToolStripMenuItem,
					this->AddSectionToolStripMenuItem, this->toolStripMenuClearLayout, this->toolStripMenuLayoutFile, this->ToolStripMenuExitProgram
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1143, 28);
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
			this->AddWallToolStripMenuItem->Size = System::Drawing::Size(131, 24);
			this->AddWallToolStripMenuItem->Text = L"Добавить стену";
			// 
			// AddHorizontalWallToolStripMenuItem
			// 
			this->AddHorizontalWallToolStripMenuItem->Name = L"AddHorizontalWallToolStripMenuItem";
			this->AddHorizontalWallToolStripMenuItem->Size = System::Drawing::Size(248, 26);
			this->AddHorizontalWallToolStripMenuItem->Text = L"Горизонтальная стена";
			this->AddHorizontalWallToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddHorizontalWall);
			// 
			// AddVerticalWallToolStripMenuItem
			// 
			this->AddVerticalWallToolStripMenuItem->Name = L"AddVerticalWallToolStripMenuItem";
			this->AddVerticalWallToolStripMenuItem->Size = System::Drawing::Size(248, 26);
			this->AddVerticalWallToolStripMenuItem->Text = L"Вертикальная стена";
			this->AddVerticalWallToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddVerticalWall);
			// 
			// AddSectionToolStripMenuItem
			// 
			this->AddSectionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->AddGrocerySectionToolStripMenuItem,
					this->AddMeatSectionToolStripMenuItem, this->AddMilkSectionToolStripMenuItem, this->AddVegetableSectionToolStripMenuItem, this->AddFishSectionToolStripMenuItem,
					this->AddBakerySectionToolStripMenuItem
			});
			this->AddSectionToolStripMenuItem->Name = L"AddSectionToolStripMenuItem";
			this->AddSectionToolStripMenuItem->Size = System::Drawing::Size(133, 24);
			this->AddSectionToolStripMenuItem->Text = L"Добавить отдел";
			// 
			// AddGrocerySectionToolStripMenuItem
			// 
			this->AddGrocerySectionToolStripMenuItem->Name = L"AddGrocerySectionToolStripMenuItem";
			this->AddGrocerySectionToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->AddGrocerySectionToolStripMenuItem->Text = L"Бакалейный";
			this->AddGrocerySectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddGrocerySection);
			// 
			// AddMeatSectionToolStripMenuItem
			// 
			this->AddMeatSectionToolStripMenuItem->Name = L"AddMeatSectionToolStripMenuItem";
			this->AddMeatSectionToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->AddMeatSectionToolStripMenuItem->Text = L"Колбасно-мясной";
			this->AddMeatSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddMeatSection);
			// 
			// AddMilkSectionToolStripMenuItem
			// 
			this->AddMilkSectionToolStripMenuItem->Name = L"AddMilkSectionToolStripMenuItem";
			this->AddMilkSectionToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->AddMilkSectionToolStripMenuItem->Text = L"Молочный";
			this->AddMilkSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddMilkSection);
			// 
			// AddVegetableSectionToolStripMenuItem
			// 
			this->AddVegetableSectionToolStripMenuItem->Name = L"AddVegetableSectionToolStripMenuItem";
			this->AddVegetableSectionToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->AddVegetableSectionToolStripMenuItem->Text = L"Овощной";
			this->AddVegetableSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddVegetableSection);
			// 
			// AddFishSectionToolStripMenuItem
			// 
			this->AddFishSectionToolStripMenuItem->Name = L"AddFishSectionToolStripMenuItem";
			this->AddFishSectionToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->AddFishSectionToolStripMenuItem->Text = L"Рыбный";
			this->AddFishSectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddFishSection);
			// 
			// AddBakerySectionToolStripMenuItem
			// 
			this->AddBakerySectionToolStripMenuItem->Name = L"AddBakerySectionToolStripMenuItem";
			this->AddBakerySectionToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->AddBakerySectionToolStripMenuItem->Text = L"Хлебобулочный";
			this->AddBakerySectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Click_AddBakerySection);
			// 
			// toolStripMenuClearLayout
			// 
			this->toolStripMenuClearLayout->Name = L"toolStripMenuClearLayout";
			this->toolStripMenuClearLayout->Size = System::Drawing::Size(87, 24);
			this->toolStripMenuClearLayout->Text = L"Очистить";
			this->toolStripMenuClearLayout->Click += gcnew System::EventHandler(this, &MyForm::Click_LayoutClear);
			// 
			// toolStripMenuLayoutFile
			// 
			this->toolStripMenuLayoutFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuLoadLayout,
					this->toolStripMenuSaveLayout
			});
			this->toolStripMenuLayoutFile->Name = L"toolStripMenuLayoutFile";
			this->toolStripMenuLayoutFile->Size = System::Drawing::Size(59, 24);
			this->toolStripMenuLayoutFile->Text = L"Файл";
			// 
			// toolStripMenuLoadLayout
			// 
			this->toolStripMenuLoadLayout->Name = L"toolStripMenuLoadLayout";
			this->toolStripMenuLoadLayout->Size = System::Drawing::Size(166, 26);
			this->toolStripMenuLoadLayout->Text = L"Загрузить";
			this->toolStripMenuLoadLayout->Click += gcnew System::EventHandler(this, &MyForm::Click_LoadLayout);
			// 
			// toolStripMenuSaveLayout
			// 
			this->toolStripMenuSaveLayout->Name = L"toolStripMenuSaveLayout";
			this->toolStripMenuSaveLayout->Size = System::Drawing::Size(166, 26);
			this->toolStripMenuSaveLayout->Text = L"Сохранить";
			this->toolStripMenuSaveLayout->Click += gcnew System::EventHandler(this, &MyForm::Click_SaveLayout);
			// 
			// ToolStripMenuExitProgram
			// 
			this->ToolStripMenuExitProgram->Name = L"ToolStripMenuExitProgram";
			this->ToolStripMenuExitProgram->Size = System::Drawing::Size(174, 24);
			this->ToolStripMenuExitProgram->Text = L"Выход из программы";
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1143, 577);
			this->Controls->Add(this->menuStrip1);
			this->DoubleBuffered = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Планировщик магазина";
			this->MouseHover += gcnew System::EventHandler(this, &MyForm::onMouseHover);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
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
	openFileDialog->Filter = "XML Files (*.xml)|*.xml";

	if (openFileDialog->ShowDialog() == Windows::Forms::DialogResult::OK) {
		XmlReader^ reader = XmlReader::Create(openFileDialog->FileName);
		try {
			graphicElements->emptyGraphicElements();
			graphicElements->deserialize(reader, this->Controls);
		}
		finally {
			reader->Close();
		}
	}
}
private: System::Void Click_SaveLayout(System::Object^ sender, System::EventArgs^ e) {
	SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
	saveFileDialog->Filter = "XML Files (*.xml)|*.xml";

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
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Indigo, 100, 100);
	this->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddMilkSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::AntiqueWhite, 100, 100);
	this->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddMeatSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::RosyBrown, 100, 100);
	this->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddFishSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Azure, 100, 100);
	this->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddBakerySection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Orange, 100, 100);
	this->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddVegetableSection(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::DraggableRectangle^ newRectangle = gcnew GraphicObject::DraggableRectangle(System::Drawing::Color::Teal, 100, 100);
	this->Controls->Add(newRectangle);
	this->graphicElements->addElement(newRectangle);
	newRectangle->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddVerticalWall(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Wall^ newWall = gcnew GraphicObject::Wall(System::Drawing::Color::Gray, Support::Orientation::Vertical, 15, 15);
	this->Controls->Add(newWall);
	this->graphicElements->addElement(newWall);
	newWall->Location = Drawing::Point(50, 50);
}
private: System::Void Click_AddHorizontalWall(System::Object^ sender, System::EventArgs^ e) {
	GraphicObject::Wall^ newWall = gcnew GraphicObject::Wall(System::Drawing::Color::Gray, Support::Orientation::Horizontal, 15, 15);
	this->Controls->Add(newWall);
	this->graphicElements->addElement(newWall);
	newWall->Location = Drawing::Point(50, 50);
}
};
}