#pragma once

#include "PagingAlgorithm.h"
#include <msclr/marshal_cppstd.h>

namespace DSALABtask1 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        Label^ Reference_String_label;
        Label^ Reference_string_val;
        Label^ Progress_Bar_Label;
        ProgressBar^ PageReplacement_ProgressBar;
        Label^ PageReplacement_Table_Label;
        array<array<Label^>^>^ pm_label_array;
        physical_memory<int>* pm;
        virtual_memory<int>* vm;
        PageReplacement* pr;
        Timer^ pageReplacementTimer;
        TableLayoutPanel^ PageReplacement_Table;
    private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;

    public:
        page_table<int>* pt;

        MyForm(void)
        {
            InitializeComponent();
            Progress_Bar_Label = gcnew Label();
            PageReplacement_ProgressBar = gcnew ProgressBar();
            PageReplacement_Table_Label = gcnew Label();
            vm = new virtual_memory<int>(35);
            pt = new page_table<int>(35);
            pt->create_page_table(*vm);
            pm = new physical_memory<int>(*pt);
            pm->allocate_physical_memory(*vm);
            pr = new PageReplacement(generate_reference_string(20,pm->get_page_table_size()),4);
            PageReplacement_Table = gcnew TableLayoutPanel();
            Reference_String_label = gcnew Label();
            Reference_string_val = gcnew Label();

            InitializePageReplacementTable();
            InitializeLabels();
            MapPhysicalMemoryToLabels();
            Map_Page_table_toLabels();

            pageReplacementTimer = gcnew Timer();
            pageReplacementTimer->Interval = 2000;
            pageReplacementTimer->Tick += gcnew System::EventHandler(this, &MyForm::OnPageReplacementTimerTick);

            pageReplacementTimer->Start();
        }
        MyForm(int processSize)
        {
            InitializeComponent();

            // Initialize your physical memory, page table, and page replacement logic here
            vm = new virtual_memory<int>(processSize);
            pt = new page_table<int>(processSize);
            pt->create_page_table(*vm);
            pm = new physical_memory<int>(*pt);
            pm->allocate_physical_memory(*vm);
            pr = new PageReplacement(generate_reference_string(20, pm->get_page_table_size()), 4);

            InitializePageReplacementTable();
            InitializeLabels();
            MapPhysicalMemoryToLabels();
            Map_Page_table_toLabels();

            pageReplacementTimer = gcnew Timer();
            pageReplacementTimer->Interval = 2000;
            pageReplacementTimer->Tick += gcnew System::EventHandler(this, &MyForm::OnPageReplacementTimerTick);

            pageReplacementTimer->Start();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
            this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this->tableLayoutPanel1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->tableLayoutPanel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
            this->tableLayoutPanel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::OutsetDouble;
            this->tableLayoutPanel1->ColumnCount = 4;
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                46.04651F)));
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                53.95349F)));
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
                90)));
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
                133)));
            this->tableLayoutPanel1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->tableLayoutPanel1->Location = System::Drawing::Point(561, 138);
            this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
            this->tableLayoutPanel1->RowCount = 20;
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 51.5625F)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 48.4375F)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
            this->tableLayoutPanel1->Size = System::Drawing::Size(400, 575);
            this->tableLayoutPanel1->TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this->tableLayoutPanel2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->tableLayoutPanel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->tableLayoutPanel2->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::OutsetDouble;
            this->tableLayoutPanel2->ColumnCount = 3;
            this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                39.22414F)));
            this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                60.77586F)));
            this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
                148)));
            this->tableLayoutPanel2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->tableLayoutPanel2->Location = System::Drawing::Point(65, 138);
            this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
            this->tableLayoutPanel2->RowCount = 1;
            this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel2->Size = System::Drawing::Size(330, 190);
            this->tableLayoutPanel2->TabIndex = 1;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label1->Location = System::Drawing::Point(187, 103);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(79, 16);
            this->label1->TabIndex = 2;
            this->label1->Text = L"Page Table";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label2->Location = System::Drawing::Point(734, 103);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(110, 16);
            this->label2->TabIndex = 3;
            this->label2->Text = L"Physical Memory";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label3->Location = System::Drawing::Point(427, 31);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(102, 16);
            this->label3->TabIndex = 4;
            this->label3->Text = L"Process Details";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
            this->ClientSize = System::Drawing::Size(973, 800);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->tableLayoutPanel2);
            this->Controls->Add(this->tableLayoutPanel1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

#pragma endregion

    private:
        void InitializeLabels()
        {
            pm_label_array = gcnew array<array<Label^>^>(20);
            for (int i = 0; i < 20; i++) {
                pm_label_array[i] = gcnew array<Label^>(4);
                for (int j = 0; j < 4; j++) {
                    // Create a panel for each cell
                    Panel^ panel = gcnew Panel();
                    panel->BorderStyle = BorderStyle::FixedSingle;
                    panel->Dock = DockStyle::Fill;

                    // Create and configure the label
                    pm_label_array[i][j] = gcnew Label();
                    pm_label_array[i][j]->TextAlign = ContentAlignment::MiddleCenter;
                    pm_label_array[i][j]->Dock = DockStyle::Fill;

                    // Add the label to the panel
                    panel->Controls->Add(pm_label_array[i][j]);

                    // Add the panel to the TableLayoutPanel
                    this->tableLayoutPanel1->Controls->Add(panel, j, i);
                }
            }
        }

        void MapPhysicalMemoryToLabels()
        {
            frame<int>** phy_memory = pm->get_phy_mem();
            for (int i = 0; i < phy_len; i++) {
                if (phy_memory[i] != nullptr) {
                    for (int j = 0; j < frame_len; j++) {
                        pm_label_array[i][j]->Text = phy_memory[i]->frame_array[j].ToString();
                    }
                }
                else {
                    for (int j = 0; j < frame_len; j++) {
                        pm_label_array[i][j]->Text = "Empty";
                    }
                }
            }
        }
        void InitializePageReplacementTable() {

            Reference_String_label->Location = Point(265, 349);
            Reference_String_label->Text = "Refernce String";
            Reference_String_label->BackColor = Color::Black;
            Reference_String_label->ForeColor = Color::White;

            Reference_string_val->Location = Point(255, 369);
            Reference_string_val->Text = msclr::interop::marshal_as<System::String^>(pr->getreferencestring());
            Reference_string_val->BackColor = Color::Black;
            Reference_string_val->ForeColor = Color::White;

            PageReplacement_Table_Label->Location = Point(65,329);
            PageReplacement_Table_Label->Size = System::Drawing::Size(150,15);
            PageReplacement_Table_Label->AutoSize = false;
            PageReplacement_Table_Label->Text = "Page Replacement Table";
            PageReplacement_Table_Label->BackColor = Color::Black;
            PageReplacement_Table_Label->ForeColor = Color::White;

            Progress_Bar_Label->Location = Point(75, 354 + pr->gettablesize() * 20 + 30);
            Progress_Bar_Label->Text = "Process Completion Bar";
            Progress_Bar_Label->Size = System::Drawing::Size(75, pr->gettablesize() * 20);
            Progress_Bar_Label->BackColor = Color::Black;
            Progress_Bar_Label->ForeColor = Color::White;

            PageReplacement_ProgressBar->Location = Point(150, 359 + pr->gettablesize() * 20 + 30);
            PageReplacement_ProgressBar->Size = System::Drawing::Size(200, 15); // Adjust size as needed
            PageReplacement_ProgressBar->Minimum = 0;
            PageReplacement_ProgressBar->Maximum = 100;
            PageReplacement_ProgressBar->Value = 0;

            PageReplacement_Table->BackColor = Color::Black;
            PageReplacement_Table->ForeColor = Color::White;
            PageReplacement_Table->BorderStyle = BorderStyle::Fixed3D;
            PageReplacement_Table->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::OutsetDouble;
            PageReplacement_Table->Location = Point(75, 359);
            PageReplacement_Table->Size = System::Drawing::Size(100, pr->gettablesize() * 20); // Adjust the height based on row count
            PageReplacement_Table->ColumnCount = 1;
            PageReplacement_Table->RowCount = pr->gettablesize();

            PageReplacement_Table->RowStyles->Clear();
            PageReplacement_Table->Controls->Clear();

            for (int i = 0; i < PageReplacement_Table->RowCount; i++) {
                PageReplacement_Table->RowStyles->Add(gcnew RowStyle(SizeType::Absolute, 15));
                Label^ label = gcnew Label();
                label->Text = "Empty";
                label->Dock = DockStyle::Fill;
                label->TextAlign = ContentAlignment::MiddleCenter;

                PageReplacement_Table->Controls->Add(label, 0, i);
            }
            this->Controls->Add(PageReplacement_Table);
            this->Controls->Add(PageReplacement_Table_Label);
            this->Controls->Add(PageReplacement_ProgressBar);
            this->Controls->Add(Progress_Bar_Label);
            this->Controls->Add(Reference_string_val);
            this->Controls->Add(Reference_String_label);
        }

        void Map_Page_table_toLabels() {
            tableLayoutPanel2->Controls->Clear();
            tableLayoutPanel2->RowCount = pm->get_page_table_size();
            tableLayoutPanel2->Size = System::Drawing::Size(330, tableLayoutPanel2->RowCount * 17.5);

            page_table<int> obj = pm->get_page_table();

            int rowIndex = 0;
            for (const auto& entry : obj.table) {
                Label^ validLabel = gcnew Label();
                Label^ vmBlockLabel = gcnew Label();
                Label^ pmBlockLabel = gcnew Label();

                validLabel->Text = entry.valid ? "Valid" : "Invalid";
                vmBlockLabel->Text = "VM Block: " + entry.vm_block_index.ToString();
                pmBlockLabel->Text = "PM Block: " + entry.pm_block_index.ToString();

                validLabel->AutoSize = true;
                vmBlockLabel->AutoSize = true;
                pmBlockLabel->AutoSize = true;

                tableLayoutPanel2->Controls->Add(validLabel, 0, rowIndex);
                tableLayoutPanel2->Controls->Add(vmBlockLabel, 1, rowIndex);
                tableLayoutPanel2->Controls->Add(pmBlockLabel, 2, rowIndex);

                rowIndex++;
            }
        }
        void OnPageReplacementTimerTick(Object^ sender, EventArgs^ e) {
            if (pr->step()) {
                std::vector<int> pageTable = pr->getPageTable();
                for (int i = 0; i < pageTable.size(); i++) {
                    if (pageTable[i] != -1) {
                        this->PageReplacement_Table->Controls[i]->Text = "" + (pageTable[i]);
                    }
                    else {
                        this->PageReplacement_Table->Controls[i]->Text = "Empty";
                    }
                }
            }
            else {
                pageReplacementTimer->Stop();
            }
            int currentReferenceStringSize = pr->getReferenceStringSize();
            int completedSteps = pr->getinitialsize() - currentReferenceStringSize;
            int progress = (completedSteps * 100) / pr->getinitialsize();
            PageReplacement_ProgressBar->Value = progress;

            if (PageReplacement_ProgressBar->Value == 100) {
                System::Windows::Forms::MessageBox::Show("Process completed with " + pr->getpagefaults() + " page faults", "Process completion", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
};
}

