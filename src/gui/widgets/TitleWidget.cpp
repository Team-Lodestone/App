/** @file TitleWidget.cpp
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/widgets/TitleWidget.h"

#include <QHBoxLayout>
#include <QLabel>

#include "Lodestone.App/LodestoneApp.h"

namespace lodestone::app::gui::widgets {
  TitleWidget::TitleWidget(QWidget* parent) {
    QLabel *titleLabel = new QLabel("Project Lodestone");
    titleLabel->setStyleSheet("font-size: 24px;");

    QLabel *versionLabel = new QLabel(QString::fromStdString(LodestoneApp::VERSION.toString()));
    versionLabel->setStyleSheet("font-size: 18px;");

    QHBoxLayout *titleLayout = new QHBoxLayout(this);
    titleLayout->setAlignment(Qt::AlignLeft);
    titleLayout->setSpacing(5);

    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(versionLabel);

    this->setLayout(titleLayout);
  }
}