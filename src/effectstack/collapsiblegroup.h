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


#ifndef COLLAPSIBLEGROUP_H
#define COLLAPSIBLEGROUP_H


#include "abstractcollapsiblewidget.h"
#include "collapsibleeffect.h"
#include "timecode.h"
#include "effectstack/keyframeedit.h"

#include <KLineEdit>
#include <QMutex>


class MyEditableLabel : public KLineEdit
{
    Q_OBJECT
public:
    explicit MyEditableLabel(QWidget * parent = 0);
    
protected:
    void mouseDoubleClickEvent( QMouseEvent *e);
};


/**)
 * @class CollapsibleEffect
 * @brief A dialog for editing markers and guides.
 * @author Jean-Baptiste Mardelle
 */

class CollapsibleGroup : public AbstractCollapsibleWidget
{
    Q_OBJECT

public:
    CollapsibleGroup(int ix, bool firstGroup, bool lastGroup, const EffectInfo &info, QWidget * parent = 0);
    ~CollapsibleGroup();
    void updateTimecodeFormat();
    void setActive(bool activate);
    int groupIndex() const;
    bool isGroup() const;
    QString infoString() const;
    bool isActive() const;
    void addGroupEffect(CollapsibleEffect *effect);
    void removeGroup(int ix, QVBoxLayout *layout);
    /** @brief Return all effects in group. */
    QList <CollapsibleEffect*> effects();
    /** @brief Return the editable title widget. */
    QWidget *title() const;
    /** @brief Return the XML data describing all effects in group. */
    QDomDocument effectsData();
    /** @brief Adjust sub effects buttons. */
    void adjustEffects();

public slots:
    void slotEnable(bool enable, bool emitInfo = true);

private slots:
    void slotSwitch();
    void slotShow(bool show);
    void slotDeleteGroup();
    void slotEffectUp();
    void slotEffectDown();
    void slotSaveGroup();
    void slotResetGroup();
    void slotUnGroup();
    void slotRenameGroup();

private:
    QList <CollapsibleEffect *> m_subWidgets;
    QMenu *m_menu;
    EffectInfo m_info;
    MyEditableLabel *m_title;
    QMutex m_mutex;
    
protected:
    void mouseDoubleClickEvent ( QMouseEvent * event );
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    
signals:
    void deleteGroup(const QDomDocument&);
    void unGroup(CollapsibleGroup *);
    void groupRenamed(CollapsibleGroup *);

};


#endif

