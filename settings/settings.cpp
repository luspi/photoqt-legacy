#include "settings.h"
#include <iostream>

Settings::Settings(QWidget *parent, QMap<QString, QVariant> glob, bool v) : QWidget(parent) {

	verbose = v;

	tabsSetup = false;

	// the settings and shortcuts
	globSet = glob;
	sh = new Shortcuts;
	sh->verbose = verbose;
	sh->loadSH();

	// Setting the background
	this->setObjectName("topsetting");
	this->setStyleSheet("QWidget#topsetting { background:rgba(0,0,0,210); }");

	// The animation, and a boolean
	ani = new QPropertyAnimation(this,"geometry");
	isShown = false;

	// The tab widget
	tabs = new TabWidget;
	tabs->makeBold(true);

	QVBoxLayout *layout = new QVBoxLayout;
	this->setLayout(layout);
	layout->addWidget(tabs);

	// Some general buttons
	CustomPushButton *setDefault = new CustomPushButton(tr("Restore Default Settings"));
	CustomPushButton *saveExit = new CustomPushButton(tr("Save Changes and Exit"));
	CustomPushButton *cancel = new CustomPushButton(tr("Exit and Discard Changes"));
	QHBoxLayout *butLay = new QHBoxLayout;
	butLay->addWidget(setDefault);
	butLay->addStretch();
	butLay->addWidget(saveExit);
	butLay->addWidget(cancel);
	butLay->addSpacing(30);
	layout->addLayout(butLay);

	// Ask for confirmation of restoring default settings
	restoreDefaultConfirm = new CustomConfirm(tr("Restore Default Settings?"),tr("Do you really want to get rid of your custom settings and set the default ones? This only resets all settings. A default set of shortcuts can be set in the shortcuts tab.") + "<br><br>" + tr("This step cannot be reversed!"),tr("Yep, I want new stuff"),tr("Um, no, not really"),QSize(400,200),this);
	restoreDefaultConfirm->showBorder("white",2);

	connect(saveExit, SIGNAL(clicked()), this, SLOT(animate()));
	connect(saveExit, SIGNAL(clicked()), this, SLOT(saveSettings()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(loadSettings()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(animate()));

	connect(setDefault, SIGNAL(clicked()), restoreDefaultConfirm, SLOT(animate()));
	connect(restoreDefaultConfirm, SIGNAL(confirmed()), this, SLOT(restoreDefaultSettings()));

	connect(ani, SIGNAL(finished()), this, SLOT(aniFinished()));

}

// Set up the tabs (only called once)
void Settings::setupTabs() {

	if(!tabsSetup) {

		qApp->setOverrideCursor(Qt::WaitCursor);

		tabsSetup = true;

		// Initiate the tabs
		tabOther = new SettingsTabOther(this,globSet,verbose);
		tabLookFeel = new SettingsTabLookAndFeel(this,globSet,verbose);
		tabThumb = new SettingsTabThumbnail(this,globSet,verbose);
		tabExif = new SettingsTabExif(this,globSet,verbose);
		tabShortcuts = new SettingsTabShortcuts(this,verbose);
		tabShortcuts->allKeyShortcuts = sh->allKeyShortcuts;
		tabShortcuts->allMouseShortcuts = sh->allMouseShortcuts;
		tabShortcuts->loadUserSetShortcuts();

		// Add the tabs
		tabs->addTab(tabLookFeel, QIcon(), tr("Look and Behaviour"));
		tabs->addTab(tabThumb, QIcon(), tr("Thumbnails"));
		tabs->addTab(tabExif, QIcon(), tr("Details"));
		tabs->addTab(tabOther, QIcon(), tr("Other Settings"));
		tabs->addTab(tabShortcuts, QIcon(), tr("Shortcuts"));
		connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged()));

		tabLookFeel->globSet = globSet;
		tabThumb->globSet = globSet;
		tabExif->globSet = globSet;
		tabOther->globSet = globSet;

		connect(tabShortcuts, SIGNAL(setDefaultShortcuts()), this, SLOT(restoreDefaultShortcuts()));


		restoreDefaultConfirm->rectShown = rectShown;
		restoreDefaultConfirm->rectHidden = rectHidden;
		restoreDefaultConfirm->rectAni = aniStart;

		tabShortcuts->detect->rectShown = rectShown;
		tabShortcuts->detect->rectHidden = rectHidden;
		tabShortcuts->detect->rectAni = aniStart;

		tabShortcuts->setDefaultConfirm->rectShown = rectShown;
		tabShortcuts->setDefaultConfirm->rectHidden = rectHidden;
		tabShortcuts->setDefaultConfirm->rectAni = aniStart;

		tabShortcuts->changeCommand->rectShown = rectShown;
		tabShortcuts->changeCommand->rectHidden = rectHidden;
		tabShortcuts->changeCommand->rectAni = aniStart;

		tabThumb->confirmClean->rectShown = rectShown;
		tabThumb->confirmClean->rectHidden = rectHidden;
		tabThumb->confirmClean->rectAni = aniStart;

		tabThumb->confirmErase->rectShown = rectShown;
		tabThumb->confirmErase->rectHidden = rectHidden;
		tabThumb->confirmErase->rectAni = aniStart;


		loadSettings();

		qApp->restoreOverrideCursor();


	}

}

void Settings::makeHide() {

	if(isShown) animate();

}

void Settings::makeShow() {

	if(!isShown) animate();

	if(!tabsSetup) setupTabs();

}

void Settings::setRect(QRect rect) {

	QRect hidden(0,-10,10,10);
	QRect anim(rect.width()/2.0,rect.height()/2.0,1,1);

	rectShown = rect;
	rectHidden = hidden;
	aniStart = anim;


	if(tabsSetup) {

		restoreDefaultConfirm->rectShown = rect;
		restoreDefaultConfirm->rectHidden = hidden;
		restoreDefaultConfirm->rectAni = anim;

		tabShortcuts->detect->rectShown = rect;
		tabShortcuts->detect->rectHidden = hidden;
		tabShortcuts->detect->rectAni = anim;

		tabShortcuts->setDefaultConfirm->rectShown = rect;
		tabShortcuts->setDefaultConfirm->rectHidden = hidden;
		tabShortcuts->setDefaultConfirm->rectAni = anim;

		tabShortcuts->changeCommand->rectShown = rect;
		tabShortcuts->changeCommand->rectHidden = hidden;
		tabShortcuts->changeCommand->rectAni = anim;

		tabThumb->confirmClean->rectShown = rect;
		tabThumb->confirmClean->rectHidden = hidden;
		tabThumb->confirmClean->rectAni = anim;

		tabThumb->confirmErase->rectShown = rect;
		tabThumb->confirmErase->rectHidden = hidden;
		tabThumb->confirmErase->rectAni = anim;

	}

	if(isShown) this->setGeometry(rectShown);
	else this->setGeometry(rectHidden);

}

// the animation function
void Settings::animate() {

	// Open widget
	if(!isShown) {

		if(ani->state() != QPropertyAnimation::Stopped)
			ani->targetObject()->setProperty(ani->propertyName(),ani->endValue());

		ani->setDuration(600);
		isShown = true;

		ani->setStartValue(aniStart);
		ani->setEndValue(rectShown);
		ani->setEasingCurve(QEasingCurve::InBack);
		ani->start();

		emit blockFunc(true);

		this->raise();

	// Close widget
	} else if(isShown) {

		if(ani->state() != QPropertyAnimation::Stopped)
			ani->targetObject()->setProperty(ani->propertyName(),ani->endValue());

		ani->setDuration(300);
		isShown = false;

		ani->setStartValue(rectShown);
		ani->setEndValue(aniStart);
		ani->setEasingCurve(QEasingCurve::OutBack);
		ani->start();

		emit blockFunc(false);

	}

}

// Load all settings
void Settings::loadSettings() {

	if(verbose) std::clog << "set: Request to Load Settings" << std::endl;

	tabLookFeel->loadSettings();
	tabThumb->loadSettings();
	tabExif->loadSettings();
	tabOther->loadSettings();

}

// Save all settings
void Settings::saveSettings() {

	if(verbose) std::clog << "set: Request to Save Settings and Shortcuts" << std::endl;

	tabShortcuts->saveShortcuts();
	sh->allKeyShortcuts = tabShortcuts->allKeyShortcutsNEW;
	sh->allMouseShortcuts = tabShortcuts->allMouseShortcutsNEW;
	sh->saveSH();

	tabLookFeel->saveSettings();
	tabThumb->saveSettings();
	tabExif->saveSettings();
	tabOther->saveSettings();

	QList<QMap<QString,QVariant> > allnewsets;
	allnewsets << tabLookFeel->updatedSet;
	allnewsets << tabThumb->updatedSet;
	allnewsets << tabExif->updatedSet;
	allnewsets << tabOther->updatedSet;

	for(int j = 0; j < allnewsets.length(); ++j) {

		QMapIterator<QString, QVariant> i(allnewsets.at(j));
		while (i.hasNext()) {
			i.next();
			globSet[i.key()] = i.value();
		}

	}

	emit updateSettings(globSet);


}

// When the animation has finished
void Settings::aniFinished() {

	tabs->setCurrentIndex(0);

	tabLookFeel->scrollbarLook->setScrollbarShown();
	tabLookFeel->scrollbarFeel->setScrollbarShown();
	tabThumb->scrollbarLook->setScrollbarShown();
	tabThumb->scrollbarTune->setScrollbarShown();
	tabShortcuts->scrollbar->setScrollbarShown();

	if(!isShown)
		this->setGeometry(rectHidden);

}

void Settings::restoreDefaultSettings() {

	if(verbose) std::clog << "set: Request to restore default settings" << std::endl;

	emit restoreDefault();

}

void Settings::restoreDefaultShortcuts() {

	if(verbose) std::clog << "set: Request to restore default shortcuts" << std::endl;

	sh->setDefault();
	tabShortcuts->allKeyShortcuts = sh->allKeyShortcuts;
	tabShortcuts->allMouseShortcuts = sh->allMouseShortcuts;
	tabShortcuts->loadUserSetShortcuts();

}

// On Tab Change, scroll to top
void Settings::tabChanged() {

	if(verbose) std::clog << "set: Current Tab Changed" << std::endl;

	if(tabs->currentIndex() == 1)
		tabThumb->setDatabaseInfo();

	tabLookFeel->scrollbarLook->setValue(0);
	tabLookFeel->scrollbarFeel->setValue(0);
	tabThumb->scrollbarLook->setValue(0);
	tabThumb->scrollbarTune->setValue(0);
	tabOther->scrollbarOther->setValue(0);
	tabOther->scrollbarFile->setValue(0);
	tabExif->scrollbar->setValue(0);
	tabShortcuts->scrollbar->setValue(0);

	tabLookFeel->tabs->setCurrentIndex(0);
	tabThumb->tabs->setCurrentIndex(0);
	tabOther->tabs->setCurrentIndex(0);

}

// Go to next tab
void Settings::nextTab() {

	if(verbose) std::clog << "set: Next Tab" << std::endl;

	int current = tabs->currentIndex();
	if(current == 4)
		current = -1;
	++current;
	tabs->setCurrentIndex(current);

}

// Go to prev tab
void Settings::prevTab() {

	if(verbose) std::clog << "set: Prev Tab" << std::endl;

	int current = tabs->currentIndex();
	if(current == 0)
		current = 5;
	--current;
	tabs->setCurrentIndex(current);

}

void Settings::paintEvent(QPaintEvent *) {
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

Settings::~Settings() { }
