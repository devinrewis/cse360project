#include "pulseratereport.h"
#include "Data/pulseratedata.h"

#include <QDebug>

PulseRateReport::PulseRateReport(QList<Data *> repository, QDate start, QDate end)
    : Report(repository, start, end)
{
    _type = PulseRateType;

    foreach (Data *data, repository)
    {
        if (data->type() == PulseRateType && start <= data->recordedDate() && end >= data->recordedDate())
        {
            _dataList.append(data);
        }
    }

    foreach (Data *data, _dataList)
    {
        qDebug() << data->toString();
    }
}


QString PulseRateReport::graphHtml() const
{
    if (_dataList.isEmpty())
        return "Not enough data for report.";

    QString html;
    html = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"
           " <html xmlns=\"http://www.w3.org/1999/xhtml\">"
           "   <head>"
           "     <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\"/>"
           "    <script type=\"text/javascript\" src=\"//www.google.com/jsapi\"></script>"
           "    <script type=\"text/javascript\">"
           "      google.load('visualization', '1', {packages: ['corechart']});"
           "    </script>"
           "    <script type=\"text/javascript\">"
           "      function drawVisualization() {"
           "        var data = google.visualization.arrayToDataTable(["
           "          ['x', 'Pulse Rate'],"
           "           %1"
           "        ]);"
           ""
           "        new google.visualization.LineChart(document.getElementById('visualization'))."
           "            draw(data, {width: 500, height: 400});"
           "      }"
           ""
           "      google.setOnLoadCallback(drawVisualization);"
           "    </script>"
           "  </head>"
           "  <body style=\"font-family: Arial;border: 0 none;\">"
           "    <div id=\"visualization\" style=\"width: 500px; height: 400px;\"></div>"
           "  </body>"
           "</html>​";

    QString formatted;

    foreach (Data *data, _dataList)
    {
        PulseRateData *prd = dynamic_cast<PulseRateData *>(data);
        formatted += "['" + prd->recordedDate().toString() + "', " + QString::number(prd->pulseRate()) + "],";
    }

    return html.arg(formatted);
}
