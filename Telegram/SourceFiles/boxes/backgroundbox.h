/*
This file is part of Telegram Desktop,
the official desktop version of Telegram messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014 John Preston, https://desktop.telegram.org
*/
#pragma once

#include "layerwidget.h"

class BackgroundInner : public QWidget, public RPCSender {
	Q_OBJECT

public:

	BackgroundInner();

	void paintEvent(QPaintEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void resizeEvent(QResizeEvent *e);

	~BackgroundInner();

signals:

	void backgroundChosen(int index);

private:

	void gotWallpapers(const MTPVector<MTPWallPaper> &result);
	void updateWallpapers();

	int32 _bgCount, _rows;
	int32 _over, _overDown;

};

class BackgroundBox : public LayeredWidget, public RPCSender {
	Q_OBJECT

public:

	BackgroundBox();
	void parentResized();
	void animStep(float64 dt);
	void keyPressEvent(QKeyEvent *e);
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
	void startHide();
	~BackgroundBox();

public slots:

	void onBackgroundChosen(int index);
	void onClose();

private:

	void hideAll();
	void showAll();

	ScrollArea _scroll;
	BackgroundInner _inner;
	int32 _width, _height;
	BottomButton _close;
	bool _hiding;

	QPixmap _cache;

	anim::fvalue a_opacity;
};
