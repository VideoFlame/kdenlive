/**************************1*************************************************
                          DocClipBase.cpp  -  description
                             -------------------
    begin                : Fri Apr 12 2002
    copyright            : (C) 2002 by Jason Wood
    email                : jasonwood@blueyonder.co.uk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <kdebug.h>

#include "docclipbase.h"
#include "docclipavfile.h"
#include "docclipproject.h"
#include "doctrackbase.h"
#include "clipmanager.h"

DocClipBase::DocClipBase() :
	m_description(""),
	m_refcount(0)
{
}

DocClipBase::~DocClipBase()
{
}

void DocClipBase::setName(const QString name)
{
	m_name = name;
}

const QString &DocClipBase::name() const
{
	return m_name;
}

void DocClipBase::setDescription(const QString &description)
{
	m_description = description;
}

const QString &DocClipBase::description() const
{
	return m_description;
}

// virtual
QDomDocument DocClipBase::toXML() {
	QDomDocument doc;

	QDomElement clip = doc.createElement("clip");
	clip.setAttribute("name", name());
	
	QDomText text = doc.createTextNode(description());
	clip.appendChild(text);
		
	doc.appendChild(clip); 
	
	return doc;
}

DocClipBase *DocClipBase::createClip(ClipManager &clipManager, const QDomElement &element)
{
	DocClipBase *clip = 0;
	QString description;
	int trackNum = 0;

	QDomNode node = element;
	node.normalize();
	
	if(element.tagName() != "clip") {
		kdWarning()	<< "DocClipBase::createClip() element has unknown tagName : " << element.tagName() << endl;
		return 0;
	}

	QDomNode n = element.firstChild();

	while(!n.isNull()) {
		QDomElement e = n.toElement();
		if(!e.isNull()) {
			QString tagName = e.tagName();
			if(e.tagName() == "avfile") {
				clip = DocClipAVFile::createClip(e);
			} else if(e.tagName() == "project") {
				clip = DocClipProject::createClip(clipManager, e);
			} else if(e.tagName() == "position") {
				trackNum = e.attribute("track", "-1").toInt();
			}		
		} else {
			QDomText text = n.toText();
			if(!text.isNull()) {
				description = text.nodeValue();
			}
		}
		
		n = n.nextSibling();
	}

	if(clip==0) {
	  kdWarning()	<< "DocClipBase::createClip() unable to create clip" << endl;
	} else {
		// setup DocClipBase specifics of the clip.
		clip->setDescription(description);
	}

	return clip;
}

