#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

typedef struct {
	char   **lines;
	Byte   cursorCol,
	       displayCol,
	       cursorDrawn,
	       cursorTimeout;
	size_t cursorLine,
	       displayLine;
	Pen    pen;
} Editor;

extern Editor *g_editorState;

enum {
	Editor_commandMode,
	Editor_insertMode
};

extern Byte Editor_mode,
            Editor_running;

void Editor_Init(void);

void Editor_RedrawAll(void);

void Editor_Step(void);

#endif // EDITOR_H_INCLUDED
