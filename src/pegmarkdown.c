#include <Python.h>
#include <string.h>

#include <glib.h>

#include "peg-markdown/markdown_lib.h"


/* The module doc strings */
PyDoc_STRVAR(pegmarkdown__doc__, "pegmarkdown is a Python binding for PEG-markdown");
PyDoc_STRVAR(pegmarkdown_markdown__doc__, "Render Markdown text into HTML.");


static PyObject *
pegmarkdown_markdown(PyObject *self, PyObject *args, PyObject *kwargs)
{
    char *out;
    static char *kwlist[] = {"text", "extensions", "output_format"};
    char *text;
    int extensions = 0; /* NONE */
    int output_format = HTML_FORMAT;
    PyObject *html;

    /* Parse arguments */
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s|ii", kwlist,
        &text, &extensions, &output_format))
        return NULL;

    out = markdown_to_string(text, extensions, output_format);
    html = Py_BuildValue("s", out);
    free(out);

    return html;
}


static PyMethodDef PegmarkdownMethods[] = {
    {"markdown",  (PyCFunction) pegmarkdown_markdown, METH_VARARGS | METH_KEYWORDS,
     pegmarkdown_markdown__doc__},
    {NULL, NULL, 0, NULL} /* Sentinel */
};


PyMODINIT_FUNC
initpegmarkdown(void)
{
    PyObject *module;

    /* The module */
    module = Py_InitModule3("pegmarkdown", PegmarkdownMethods, pegmarkdown__doc__);
    if (module == NULL)
        return;

    /* Markdown extensions */
    PyModule_AddIntConstant(module, "EXT_SMART", EXT_SMART);
    PyModule_AddIntConstant(module, "EXT_NOTES", EXT_NOTES);
    PyModule_AddIntConstant(module, "EXT_FILTER_HTML", EXT_FILTER_HTML);
    PyModule_AddIntConstant(module, "EXT_FILTER_STYLES", EXT_FILTER_STYLES);

    ///* Output formats */
    PyModule_AddIntConstant(module, "HTML_FORMAT", HTML_FORMAT);
    PyModule_AddIntConstant(module, "LATEX_FORMAT", LATEX_FORMAT);
    PyModule_AddIntConstant(module, "ODF_FORMAT", ODF_FORMAT);
    PyModule_AddIntConstant(module, "GROFF_MM_FORMAT", GROFF_MM_FORMAT);
}
