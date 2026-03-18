/** @file MainScreen.h
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_MAINSCREEN_H
#define LODESTONE_MAINSCREEN_H
#include <QVBoxLayout>
#include <QWidget>

namespace lodestone::app {
  class LodestoneApp;
}

namespace lodestone::app::gui::screens {
  class MainScreen : public QWidget {
    Q_OBJECT

  public:
    MainScreen(LodestoneApp *app, QWidget *parent = nullptr);

  private slots:
    void onAboutButtonClicked();

  private:
    LodestoneApp *m_app;

    QVBoxLayout *m_layout;
    QHBoxLayout *m_toolbar;
  };
}

#endif // LODESTONE_MAINSCREEN_H