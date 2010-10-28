

#ifndef _Log_
#include "Log.h"
#endif






#define kLogLineCount 15
#define kDisplayLineCount 8


static string _log[kLogLineCount];
static int _logEntryIndex;			//	index where the next entry goes
static int _logDisplayIndex;		//	index where we start the display
static int _logStartIndex;			//	index of the first entry
static bool _logDisplaying;				//	true if we're showing the log and responding to nxt button presses to scroll





int _LogGetRealIndexForVirtualIndex(int virtualIndex)
{
	int real = virtualIndex % kLogLineCount;
	return real;
}


int _LogEntryCount()
{
	return _logEntryIndex - _logStartIndex;
}

int _LogLastPossibleDisplayIndex()
{
	int entryCount = _LogEntryCount();
	if ( entryCount > kDisplayLineCount )	//	we have more entries than screen space
	{
		return _logEntryIndex - entryCount;	//	display the last page
	}
	else
	{
		return _logStartIndex;	//	we have less than a page to show, so show as much as we can
	}
}

void _LogDrawString(int screenIndex, int logIndex)
{
	int realIndex = _LogGetRealIndexForVirtualIndex(logIndex);
	nxtDisplayCenteredTextLine(screenIndex, _log[realIndex]);
}



void _DrawLog()
{
	int logIndex = _logDisplayIndex;
	for ( int i = 0; i < kDisplayLineCount; i++ )
	{
		_LogDrawString(i, logIndex);
	}
}

void _DrawLogIfNecessary()
{
	if ( _logDisplaying ) _DrawLog();
}


void LogClear()
{
	for ( int i = 0; i < kLogLineCount; i++ )
	{
		strcpy(_log[i], "");	//	blank out all the strings
	}

	_logDisplayIndex = 0;
	_logEntryIndex = 0;
	_logStartIndex = 0;
}

void LogHide()
{
	_logDisplaying = false;
	eraseDisplay();
}

void LogShow()
{
	_logDisplaying = true;
	_DrawLog();
}



void LogString(string str)
{
	int realIndex = _LogGetRealIndexForVirtualIndex(_logEntryIndex);
	strcpy(_log[realIndex], str);

	bool displayLatest = (_logDisplayIndex == _LogLastPossibleDisplayIndex());

	++_logEntryIndex;
	if ( _logEntryIndex >= kLogLineCount ) ++_logStartIndex;
	if ( displayLatest ) _logDisplayIndex = _LogLastPossibleDisplayIndex();

	_DrawLogIfNecessary();
}


void LogScrollUp()
{
	if ( _logDisplayIndex > _logStartIndex ) --_logDisplayIndex;
}

void LogScrollDown()
{
	if ( _logDisplayIndex < _LogLastPossibleDisplayIndex() ) ++_logDisplayIndex;
}


void LogScrollToBottom()
{
	_logDisplayIndex = _LogLastPossibleDisplayIndex();
	_DrawLogIfNecessary();
}
