/***************************************************************************
 *   Copyright (C) 2008 by Jean-Baptiste Mardelle (jb@kdenlive.org)        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef SLIDESHOWCLIP_H
#define SLIDESHOWCLIP_H


#include "definitions.h"
#include "docclipbase.h"
#include "timecode.h"
#include "ui_slideshowclip_ui.h"

#include <KIO/PreviewJob>

class SlideshowClip : public QDialog
{
    Q_OBJECT

public:
    SlideshowClip(Timecode tc, QWidget * parent = 0);
    virtual ~ SlideshowClip();
    /** return selected path for slideshow in MLT format */
    QString selectedPath() const;
    QString clipName() const;
    QString clipDuration() const;
    QString lumaDuration() const;
    int imageCount() const;
    bool loop() const;
    bool fade() const;
    QString lumaFile() const;
    int softness() const;

    /** @brief Check if there are several files with filename pattern, like: image_001.jpg, image_002.jpg,... */
    static int sequenceCount(KUrl file);

private slots:
    void parseFolder();
    void slotEnableLuma(int state);
    void slotEnableThumbs(int state);
    void slotEnableLumaFile(int state);
    void slotUpdateDurationFormat(int ix);
    void slotGenerateThumbs();
    void slotSetPixmap(const KFileItem &fileItem, const QPixmap &pix);
    /** @brief Display correct widget depenging on user choice (mimetype or pattern method). */
    void slotMethodChanged(bool active);

private:
    Ui::SlideshowClip_UI m_view;
    int m_count;
    Timecode m_timecode;
    KIO::PreviewJob *m_thumbJob;
};


#endif

