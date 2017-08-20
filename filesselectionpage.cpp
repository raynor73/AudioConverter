#include "filesselectionpage.h"
#include "ui_filesselectionpage.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QListWidgetItem>
#include <QDebug>

const QString FilesSelectionPage::PREV_SOURCE_DIR_KEY = "wizard/files/source";
const QString FilesSelectionPage::PREV_DEST_DIR_KEY = "wizard/files/dest";

FilesSelectionPage::FilesSelectionPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::FilesSelectionPage),
	m_wizardViewModel(wizardViewModel)
{
	ui->setupUi(this);

	if (m_settings.contains(PREV_SOURCE_DIR_KEY))
		m_sourceDir = m_settings.value(PREV_SOURCE_DIR_KEY).toString();

	if (m_settings.contains(PREV_DEST_DIR_KEY)) {
		m_destDirPath = m_settings.value(PREV_DEST_DIR_KEY).toString();
		ui->destDirLabel->setText(m_destDirPath);
	}

	connect(ui->pickFilesButton, &QPushButton::clicked, [this]() {
		QString filter;
		if (m_wizardViewModel.convertionWay() == ConverterWizardViewModel::WAV_TO_MP3)
			filter = tr("WAV files (*.wav)");
		else
			filter = tr("MP3 files (*.mp3)");

		QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Select one or more files to open"),
															  m_sourceDir.isEmpty() ? QDir::homePath() : m_sourceDir,
															  filter);
		if (filePaths.size() >= 1) {
			m_sourceDir = QFileInfo(filePaths[0]).dir().absolutePath();
			m_wizardViewModel.sourceFilePaths().clear();
			m_wizardViewModel.sourceFilePaths() = filePaths;

			for (auto path : filePaths) {
				new QListWidgetItem(path, ui->filePathsListWidget);
			}
		}
	});

	connect(ui->pickDirButton, &QPushButton::clicked, [this]() {
		QString destDirPath = QDir::homePath();
		if (!m_destDirPath.isEmpty())
			destDirPath = QFileInfo(m_destDirPath).dir().absolutePath();

		QString dirPath = QFileDialog::getExistingDirectory(this, tr("Select destination directory"), destDirPath);
		if (!dirPath.isEmpty()) {
			m_destDirPath = dirPath;
			m_wizardViewModel.setDestDirPath(m_destDirPath);
			ui->destDirLabel->setText(m_destDirPath);
		}
	});
}

FilesSelectionPage::~FilesSelectionPage()
{
	if (!m_sourceDir.isEmpty())
		m_settings.setValue(PREV_SOURCE_DIR_KEY, m_sourceDir);

	if (!m_destDirPath.isEmpty())
		m_settings.setValue(PREV_DEST_DIR_KEY, m_destDirPath);

	delete ui;
}
