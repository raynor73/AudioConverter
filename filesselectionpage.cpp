#include "filesselectionpage.h"
#include "ui_filesselectionpage.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QListWidgetItem>

FilesSelectionPage::FilesSelectionPage(ConverterWizardViewModel &wizardViewModel, QWidget *parent) :
	QWizardPage(parent),
	ui(new Ui::FilesSelectionPage),
	m_wizardViewModel(wizardViewModel)
{
	ui->setupUi(this);

	if (!m_wizardViewModel.destDirPath().isEmpty())
		ui->destDirLabel->setText(m_wizardViewModel.destDirPath());

	connect(ui->pickFilesButton, &QPushButton::clicked, [this]() {
		QString filter;
		if (m_wizardViewModel.convertionWay() == ConverterWizardViewModel::WAV_TO_MP3)
			filter = tr("WAV files (*.wav)");
		else
			filter = tr("MP3 files (*.mp3)");

		QString dir = m_wizardViewModel.sourceDirPath().isEmpty() ? QDir::homePath() :
																	m_wizardViewModel.sourceDirPath();
		QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Select one or more files to open"), dir,
															  filter);
		if (filePaths.size() >= 1) {
			m_wizardViewModel.setSourceDirPath(QFileInfo(filePaths[0]).dir().absolutePath());
			m_wizardViewModel.sourceFilePaths().clear();
			m_wizardViewModel.sourceFilePaths() = filePaths;

			ui->filePathsListWidget->clear();
			for (auto path : filePaths) {
				new QListWidgetItem(path, ui->filePathsListWidget);
			}
		}

		emit completeChanged();
	});

	connect(ui->pickDirButton, &QPushButton::clicked, [this]() {
		QString dir = m_wizardViewModel.destDirPath().isEmpty() ? QDir::homePath() :
																	m_wizardViewModel.destDirPath();
		QString selectedDirPath = QFileDialog::getExistingDirectory(this, tr("Select destination directory"), dir);
		if (!selectedDirPath.isEmpty()) {
			m_wizardViewModel.setDestDirPath(selectedDirPath);
			ui->destDirLabel->setText(selectedDirPath);
		}

		emit completeChanged();
	});
}

bool FilesSelectionPage::isComplete() const
{
	return m_wizardViewModel.sourceFilePaths().size() > 0 && !m_wizardViewModel.destDirPath().isEmpty();
}

FilesSelectionPage::~FilesSelectionPage()
{
	delete ui;
}
