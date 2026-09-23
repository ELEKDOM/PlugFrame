// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
//
// This file is part of PlugFrame.
//
// PlugFrame is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PlugFrame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//
#include <QFile>
#include <QSaveFile>
#include <QMessageBox>
#include "guisimplefileeditor.h"
#include "ui_guisimplefileeditor.h"

configurator::GuiSimpleFileEditor::GuiSimpleFileEditor(QWidget *parent)
    : GuiEditableWidget(parent)
    , ui(new Ui::guiSimpleFileEditor)
{
    ui->setupUi(this);

    connect(ui->saveButton,SIGNAL(clicked(bool)),this,SLOT(onSave()));
    connect(ui->plainTextEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
}

configurator::GuiSimpleFileEditor::~GuiSimpleFileEditor()
{
    delete ui;
}

void configurator::GuiSimpleFileEditor::edit(const QString &filePath)
{
    QFile file{filePath};

    ui->editedFile->setText(filePath);
    if (file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QByteArray buf;

            buf = file.readAll();
            m_filePath = filePath;
            ui->plainTextEdit->setPlainText(buf);

            ui->saveButton->setEnabled(false);
            emit isClean();
        }
        else
        {
            QMessageBox::information(this,filePath,tr("Open error!"));
        }
    }
    else
    {
        QMessageBox::information(this,filePath,tr("This file does not exist!"));
    }
}

void configurator::GuiSimpleFileEditor::onSave()
{
    if(!m_filePath.isEmpty())
    {
        QString text{ui->plainTextEdit->toPlainText()};
        QByteArray outData{text.toUtf8()};
        QSaveFile outFile{m_filePath};
        bool ok;

        ok = outFile.open(QIODevice::WriteOnly);
        if (ok)
        {
            ok = outFile.write(outData) == outData.size();
        }
        if (ok)
        {
            outFile.commit();

            ui->saveButton->setEnabled(false);
            emit isClean();
        }

        if(!ok)
        {
            QMessageBox::information(this,m_filePath,tr("Save failed!"));
        }
    }
}

void configurator::GuiSimpleFileEditor::onTextChanged()
{
    ui->saveButton->setEnabled(true);
    emit isDirty();
}
