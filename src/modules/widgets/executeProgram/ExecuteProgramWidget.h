/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2018 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
* Copyright (C) 2016 Piotr Wójcik <chocimier@tlen.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_EXECUTEPROGRAMWIDGET_H
#define OTTER_EXECUTEPROGRAMWIDGET_H

#include "../../../core/ActionsManager.h"
#include "../../../core/SessionsManager.h"
#include "../../../ui/ToolButtonWidget.h"

#include <QtCore/QPointer>

namespace Otter
{

class Action;
class Window;

class ExecuteProgramWidget : public ToolButtonWidget
{
    Q_OBJECT

public:
    explicit ExecuteProgramWidget(int identifier, Window *window, const ToolBarsManager::ToolBarDefinition::Entry &definition, QWidget *parent = nullptr);

    int getIdentifier() const;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    bool event(QEvent *event) override;

protected slots:
    void setWindow(Window *window);

private:
    Action *m_action;
};

}

#endif
