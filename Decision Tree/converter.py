import pandas
import easygui
easygui.egdemo

def getFile():
    filename = easygui.fileopenbox()
    read_file = pandas.read_csv(filename)
    if filename.endswith('.csv')==False:
        title = "Enter File Name"
        text = "Converted File Name:"
        d_text = "*.csv"
        saveFileName = easygui.enterbox(text, title, d_text)
        if saveFileName.endswith('.csv')==False:
            saveFileName += '.csv'
        read_file.to_csv(saveFileName, index=None)
        return saveFileName

    else:
        return filename