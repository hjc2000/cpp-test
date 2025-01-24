#pragma once
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace test
{
	class MainWindow :
		public QMainWindow
	{
	public:
		MainWindow();
	};
} // namespace test
