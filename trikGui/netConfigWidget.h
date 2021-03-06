/* Copyright 2013 Roman Kurbatov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

/* This file was modified by Yurii Litvinov to make it comply with the requirements of trikRuntime
 * project. See git revision history for detailed changes. */

#pragma once

#include <QtCore/qglobal.h>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	#include <QtGui/QLabel>
	#include <QtGui/QTextEdit>
	#include <QtGui/QVBoxLayout>
	#include <QtGui/QListView>
#else
	#include <QtWidgets/QLabel>
	#include <QtWidgets/QTextEdit>
	#include <QtWidgets/QVBoxLayout>
	#include <QtWidgets/QListView>
#endif

#include <QtCore/QList>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

namespace trikGui {

/// Widget that shows current network configuration information like IP address.
class NetConfigWidget : public QWidget
{
	Q_OBJECT

public:
	explicit NetConfigWidget(QWidget *parent = 0);
	~NetConfigWidget();

	static QString menuEntry();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	QLabel mTitleLabel;
	QListView mConfigView;
	QList<QStandardItem *> mConfigItems;
	QStandardItemModel mConfigModel;
	QVBoxLayout mLayout;

	void generateNetConfigList();
};

}
