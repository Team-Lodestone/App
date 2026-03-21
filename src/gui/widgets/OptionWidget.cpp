/** @file OptionWidget.cpp
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/widgets/OptionWidget.h"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <iostream>

namespace lodestone::app::gui::widgets {
    OptionWidget::OptionWidget(const option::IGuiOption *option, QWidget *parent) : QWidget(parent) {
        this->m_layout = new QVBoxLayout(this);

        // init groupbox
        this->m_groupBox = new QGroupBox(QString::fromStdString(option->displayName()));

        // init groupbox layout
        this->m_groupBoxLayout = new QVBoxLayout();
        this->m_groupBoxLayout->setSpacing(10);

        // init groupbox main layout (center)
        this->m_groupBoxMainLayout = new QVBoxLayout();
        //footer layout
        this->m_groupBoxFooterLayout = new QHBoxLayout();

        //add main gb children
        const QString description = QString::fromStdString(option->description());
        this->m_groupBoxMainLayout->addWidget(new QLabel(description));

        //add gb footer children
        this->m_errorLabel = new QLabel();
        this->m_errorLabel->setPixmap(QIcon::fromTheme("dialog-error").pixmap(64, 64));
        this->m_errorLabel->setAlignment(Qt::AlignHCenter);

        this->m_errorLabel->setVisible(false);

        this->m_groupBoxFooterLayout->addWidget(this->m_errorLabel);

        //set groupbox layout
        this->m_groupBox->setLayout(this->m_groupBoxLayout);

        // add groupbox child layouts
        this->m_groupBoxLayout->addLayout(this->m_groupBoxMainLayout);
        this->m_groupBoxLayout->addLayout(this->m_groupBoxFooterLayout);

        this->m_layout->addWidget(this->m_groupBox);
    }

    void OptionWidget::setErrorMessage(const QString &string) const {
        this->m_errorLabel->setText(string);
    }

    void OptionWidget::setErrorVisible(const bool visible) const {
        this->m_errorLabel->setVisible(visible);
    }
}