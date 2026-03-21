/** @file OptionWidget.h
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_OPTIONWIDGET_H
#define LODESTONE_OPTIONWIDGET_H
#include "Lodestone.App/gui/options/GuiOption.h"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace lodestone::app::gui::widgets {
    class OptionWidget : public QWidget {
        Q_OBJECT
    public:
        explicit OptionWidget(const option::IGuiOption *option, QWidget *parent = nullptr);

        QVBoxLayout *mainLayout() const {
            return this->m_groupBoxMainLayout;
        }

        QHBoxLayout *footerLayout() const {
            return this->m_groupBoxFooterLayout;
        }

        void setErrorMessage(const QString &string) const;
        void setErrorVisible(bool visible) const;
    private:
        QVBoxLayout *m_layout;

        QGroupBox *m_groupBox;
        QVBoxLayout *m_groupBoxMainLayout;
        QVBoxLayout *m_groupBoxLayout;
        QHBoxLayout *m_groupBoxFooterLayout;

        QLabel *m_errorLabel;
    };
}

#endif // LODESTONE_OPTIONWIDGET_H