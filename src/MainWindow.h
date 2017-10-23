#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include "cutter.h" // only needed for ut64
#include "widgets/DisassemblyWidget.h"
#include "widgets/DisassemblerGraphView.h"
#include "widgets/SidebarWidget.h"
#include "widgets/HexdumpWidget.h"
#include "utils/Configuration.h"

#include <QMainWindow>
#include <QList>

class CutterCore;
class DockWidget;
class Omnibar;
class PreviewWidget;
class Notepad;
class SideBar;
class Highlighter;
class AsciiHighlighter;
class GraphicsBar;
class FunctionsWidget;
class ImportsWidget;
class ExportsWidget;
class SymbolsWidget;
class RelocsWidget;
class CommentsWidget;
class StringsWidget;
class FlagsWidget;
class Dashboard;
class QLineEdit;
class SdbDock;
class QAction;
class SectionsDock;
class ConsoleWidget;
class EntrypointWidget;
class DisassemblerGraphView;

class QDockWidget;

namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool responsive;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void openNewFile(const QString &fn, int anal_level = -1, QList<QString> advanced = QList<QString>());
	void openProject(const QString &project_name);

    void initUI();
    void finalizeOpen();

    /*!
     * @param quit whether to show destructive button in dialog
     * @return if quit is true, false if the application should not close
     */
    bool saveProject(bool quit = false);

    /*!
     * @param quit whether to show destructive button in dialog
     * @return if quit is true, false if the application should not close
     */
	bool saveProjectAs(bool quit = false);

    void start_web_server();
    void closeEvent(QCloseEvent *event) override;
    void readSettings();
    void setFilename(const QString &fn);
    void updateFrames();
    void refreshFunctions();
    void refreshComments();
    void addOutput(const QString &msg);
    void addDebugOutput(const QString &msg);
    void sendToNotepad(const QString &txt);
    void toggleSideBarTheme();
    void refreshOmniBar(const QStringList &flags);

signals:
    void cursorAddressChanged(RVA offset); // TODO cursor should be handled by its own widget

public slots:

    void dark();

    void def_theme();

    void on_actionEntry_points_triggered();
    void on_actionFunctions_triggered();
    void on_actionImports_triggered();
    void on_actionExports_triggered();
    void on_actionSymbols_triggered();
    void on_actionReloc_triggered();
    void on_actionStrings_triggered();
    void on_actionSections_triggered();
    void on_actionFlags_triggered();
    void on_actionComents_triggered();
    void on_actionNotepad_triggered();

    void on_actionLock_triggered();

    void on_actionLockUnlock_triggered();

    void on_actionTabs_triggered();

    void on_actionhide_bottomPannel_triggered();

    void lockUnlock_Docks(bool what);

    void on_actionDashboard_triggered();

    void on_actionDark_Theme_triggered();

    void on_actionRun_Script_triggered();

    void toggleResponsive(bool maybe);

    void backButton_clicked();

    void refreshVisibleDockWidgets();

private slots:

    void on_actionMem_triggered();

    void on_actionAbout_triggered();

    void on_actionRefresh_Panels_triggered();

    void on_actionCalculator_triggered();

    void on_actionCreate_File_triggered();

    void on_actionAssembler_triggered();

    void on_actionDisasAdd_comment_triggered();

    void restoreDocks();

    void on_actionDefaut_triggered();

    void hideAllDocks();

    void showDefaultDocks();

    void on_actionFunctionsRename_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();
	void on_actionSaveAs_triggered();

    void on_actionWhite_Theme_triggered();

    void on_actionSDB_browser_triggered();

    void on_actionLoad_triggered();

    void on_actionShow_Hide_mainsidebar_triggered();

    void on_actionForward_triggered();

    void on_actionTabs_on_Top_triggered();

    void on_actionReset_settings_triggered();

    void on_actionQuit_triggered();

    void on_actionRefresh_contents_triggered();

    void on_actionAsmOptions_triggered();

    void projectSaved(const QString &name);

private:
    CutterCore       *core;
    DisassemblyWidget  *disassemblyDock;
    SidebarWidget    *sidebarDock;
    HexdumpWidget    *hexdumpDock;
    QDockWidget      *graphDock;
    DisassemblerGraphView *graphView;
    QDockWidget      *asmDock;
    QDockWidget      *calcDock;
    Omnibar          *omnibar;
    SideBar          *sideBar;
    PreviewWidget     *previewDock;
    Notepad          *notepadDock;
    Configuration   *configuration;

    bool doLock;
    void refreshMem();
    ut64 hexdumpTopOffset;
    ut64 hexdumpBottomOffset;
    RVA cursorAddress;
    QString filename;
    QList<QDockWidget *> dockWidgets;
    std::unique_ptr<Ui::MainWindow> ui;
    Highlighter      *highlighter;
    AsciiHighlighter *hex_highlighter;
    GraphicsBar      *graphicsBar;
    EntrypointWidget *entrypointDock;
    FunctionsWidget  *functionsDock;
    ImportsWidget    *importsDock;
    ExportsWidget    *exportsDock;
    SymbolsWidget    *symbolsDock;
    RelocsWidget     *relocsDock;
    CommentsWidget   *commentsDock;
    StringsWidget    *stringsDock;
    FlagsWidget      *flagsDock;
    Dashboard        *dashboardDock;
    QLineEdit        *gotoEntry;
    SdbDock          *sdbDock;
    QAction          *sidebar_action;
    SectionsDock     *sectionsDock;
    ConsoleWidget    *consoleWidget;

    void toggleDockWidget(QDockWidget *dock_widget);

public:
    RVA getCursorAddress() const        { return cursorAddress; }
    QString getFilename() const         { return filename; }
    void setCursorAddress(RVA addr);
};

#endif // MAINWINDOW_H