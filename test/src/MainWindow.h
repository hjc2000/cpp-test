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
		MainWindow()
		{
			setWindowTitle("带有侧边栏的 Hello World");

			// 创建一个中央部件
			QWidget *centralWidget = new QWidget{this};

			// 创建 QVBoxLayout 实例并将其设置为中央部件的布局
			QVBoxLayout *layout = new QVBoxLayout{centralWidget};
			layout->setAlignment(Qt::Alignment{Qt::AlignmentFlag::AlignTop});

			// 添加一些按钮到布局中作为示例
			QPushButton *button1 = new QPushButton("按钮 1", centralWidget);
			layout->addWidget(button1);

			QPushButton *button2 = new QPushButton("按钮 2", centralWidget);
			layout->addWidget(button2);

			QPushButton *button3 = new QPushButton("按钮 3", centralWidget);
			layout->addWidget(button3);

			// 设置中央部件
			setCentralWidget(centralWidget);
		}
	};
} // namespace test
