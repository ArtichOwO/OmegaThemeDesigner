#include "mainwindow.h"
#include "ui_mainwindow.h"

using json = nlohmann::json;

extern json jsonFileContentParsed;
json jsonFileContentParsed;

extern bool isProjectOpen;
bool isProjectOpen = false;

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);

    QObject::connect(ui->actionOpen,&QAction::triggered, this, &MainWindow::loadProject);
    QObject::connect(ui->actionSave,&QAction::triggered, this, &MainWindow::saveJSON);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadProject()
{
    QString name = qgetenv("USER");
    if (name.isEmpty()) {
        name = qgetenv("USERNAME");
    }

    QFileDialog dialogOpen;
    dialogOpen.setFileMode(QFileDialog::AnyFile);

    QString jsonPath = QFileDialog::getOpenFileName(this,
            tr("Open Theme project"), "/Users/"+name,
            tr("JSON (*.json);;All Files (*)"));

    string JSONPathString = jsonPath.toStdString();
    cout << JSONPathString << endl;

    string jsonFileContent;

    ifstream fichier(JSONPathString);
    if (fichier) {
        string ligne;
        while(getline(fichier, ligne)){
            jsonFileContent.append(ligne);
        }
        jsonFileContentParsed = json::parse(jsonFileContent);

        QString themeName = QString::fromStdString(jsonFileContentParsed["name"].get<std::string>());
        QString iconsFolder = QString::fromStdString(jsonFileContentParsed["icons"].get<std::string>());

        ui->themeNameLineEdit->insert(themeName);
        ui->iconsFolderLineEdit->insert(iconsFolder);
        isProjectOpen = true;
        return true;
    } else {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        return false;
    }
}

void MainWindow::saveJSON() {
    if (isProjectOpen) {
        jsonFileContentParsed["name"] = ui->themeNameLineEdit->text().toStdString();
        jsonFileContentParsed["icons"] = ui->iconsFolderLineEdit->text().toStdString();
    } else {
        cout << "Nope, can't save" << endl;
    }
    return;
}

/*void MainWindow::testTestTest() {
    cout << jsonFileContentParsed["colors"]["PrimaryText"] << endl;
    return;
}*/
