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

#include "ExecuteProgramWidget.h"
#include "../../../core/Application.h"
#include "../../../ui/Action.h"
#include "../../../ui/MainWindow.h"
#include "../../../ui/ToolBarWidget.h"
#include "../../../ui/Window.h"

#include <QtGui/QMouseEvent>
#include <QtWidgets/QToolTip>
#include <QProcess>

namespace Otter
{

ExecuteProgramWidget::ExecuteProgramWidget(int identifier, Window *window, const ToolBarsManager::ToolBarDefinition::Entry &definition, QWidget *parent) : ToolButtonWidget(definition, parent),
    m_action(new Action(identifier, definition.parameters, definition.options, ActionExecutor::Object(window, window), this))
{
    setDefaultAction(m_action);
    setWindow(window);

    const ToolBarWidget *toolBar(qobject_cast<ToolBarWidget*>(parent));

    if (toolBar && toolBar->getDefinition().isGlobal())
    {
        connect(toolBar, &ToolBarWidget::windowChanged, this, &ExecuteProgramWidget::setWindow);
    }
}

void ExecuteProgramWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
    {
        ToolButtonWidget::mouseReleaseEvent(event);

        return;
    }

    int identifier(m_action->getIdentifier());
    QVariantMap parameters(m_action->getParameters());


    Application::triggerAction(identifier, parameters, this);

    setDefaultAction(nullptr);

    ToolButtonWidget::mouseReleaseEvent(event);

    setDefaultAction(m_action);
}

void ExecuteProgramWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->ignore();
}

void ExecuteProgramWidget::dropEvent(QDropEvent *event)
{
    event->ignore();
}

void ExecuteProgramWidget::setWindow(Window *window)
{
    MainWindow *mainWindow(MainWindow::findMainWindow(this));

    m_action->setExecutor(ActionExecutor::Object(mainWindow, mainWindow));
}

int ExecuteProgramWidget::getIdentifier() const
{
    return m_action->getIdentifier();
}

bool ExecuteProgramWidget::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip)
    {
        QToolTip::showText(static_cast<QHelpEvent*>(event)->globalPos(), text() + (m_action->shortcut().isEmpty() ? QString() : QLatin1String(" (") + m_action->shortcut().toString(QKeySequence::NativeText) + QLatin1Char(')')));

        return true;
    }

    return ToolButtonWidget::event(event);
}

}
