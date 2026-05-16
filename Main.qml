import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 6.0
import QtCharts

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Consdeau")

    property int seuilCoupure: 100;
    property int seuilSonor: 50;
    property int seuilVisuel: 30;



    Connections{
        target: bdd
        onDeuxCharts:{
            rectangle_chartSeuil.visible = true;
            rectangle_chartJourAndMois.anchors.fill = undefined;
            rectangle_chartJourAndMois.width = pageCharts.width * 2/3
            rectangle_chartJourAndMois.height = 470

        }
        onJoursAndMois:{
            boutonChangeJourAndMois.visible = true
        }
        onNoChartJourAndMois:{
            chartJourAndMois.visible = false
        }
        onMois:{
            axisXX.categories = ["1J-5J", "6j-10j", "11j-15j", "16j-20j", "21j-25j", "26j-31j"]
            console.log("-----------------------mois----------------------------")
            axisXX.mois = true
        }
        onJours:{
            axisXX.categories =  ["1h-4h", "5h-8h", "9h-12h", "13h-16h", "17h-20h", "20h-24h"]
            console.log("-----------------------jours----------------------------")
            axisXX.mois = false
        }

    }
    Connections{
        target: bdd
        function onConsoTempsReel(ec, ef, placeDansCharts){
            barChaude.replace(placeDansCharts, barChaude.at(placeDansCharts) + ec)
            barFroide.replace(placeDansCharts, barFroide.at(placeDansCharts) + ef)
            percentChaude.replace(0, percentChaude.at(0) + ec)
            percentFroide.replace(0, percentFroide.at(0) + ef)

        }
    }


    Connections{
        target: serveur
        function onChangClasse(enbddec, enbddef){
            bdd.InBdd(enbddec, enbddef, !axisXX.mois)
            console.log(!axisXX.mois)

        }
    }

    Column {
        id: page1
        width: parent.width
        height: parent.height
        visible: true


        Row {
            id: rowtop
            width: parent.width
            height: parent.height/6

            Rectangle{
                id:rowtopcolor
                width: parent.width
                height: parent.height
                color: "#0A1128"

                Label {
                    id: titre
                    height: parent.height
                    text: qsTr("Connexion")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.styleName: "Bold"
                    font.family: "Verdana"
                    font.pointSize: 56
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#ffffff"

                }
            }




        }
        Rectangle{
            id: sectioncolor
            width: parent.width
            height: parent.height - rowtop.height
            color: "#243E94"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#667eea"
                }

                GradientStop {
                    position: 1
                    color: "#764ba2"
                }
                orientation: Gradient.Vertical
            }


            Grid {
                id: section
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                columns: 5
                spacing: 10
                rowSpacing: 30


                Repeater {
                    id: sectionrepeater
                    model: bdd.perso

                    Item {
                        id: sectionitem
                        width: 150
                        height: 200






                        Rectangle{
                            id: sectionrectangle
                            color: "#00ffffff"
                            anchors.fill: parent

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    boutonChangeJourAndMois.visible = false
                                    rectangle_chartSeuil.visible = false;
                                    rectangle_chartJourAndMois.anchors.fill = pageCharts;
                                    chartJourAndMois.visible = true




                                    bdd.informationUser(bdd.prenom[index]);
                                    page1.visible = false;
                                    page2.visible = true;
                                    seuilSonor.clear()
                                    seuilSonor.append(-5, bdd.user["sonor"])
                                    seuilSonor.append(5, bdd.user["sonor"])
                                    seuilVisuel.clear()
                                    seuilVisuel.append(-5, bdd.user["visuel"])
                                    seuilVisuel.append(5, bdd.user["visuel"])
                                    seuilCoupure.clear()
                                    seuilCoupure.append(-5, bdd.user["coupure"])
                                    seuilCoupure.append(5, bdd.user["coupure"])
                                    ay.max = bdd.user["coupure"]


                                    imgRowPerso.source = "img/"+bdd.user.img+".png"
                                    label.text = qsTr("Bonjour, " + bdd.user.prenom)
                                    for(let i = 0; i < 6; i++){
                                        barChaude.replace(i,bdd.ec[i]);
                                        // console.log("eau chaude : " + bdd.ec[i]);
                                        barFroide.replace(i,bdd.ef[i]);
                                        // console.log("eau froide : " + bdd.ef[i]);
                                    }

                                    bdd.gestionCharts(false)
                                    let totalef = 0.0
                                    let totalec = 0.0
                                    for(let i = 0; i < 6; i++){
                                        //console.log(totalef, "       " ,totalec)
                                        totalef +=  bdd.ef[i]
                                        totalec += bdd.ec[i]
                                    }
                                    percentChaude.replace(0, totalec)
                                    percentFroide.replace(0, totalef)
                                    bdd.informationUser(bdd.prenom[index]);
                                    serveur.openElec()
                                    timerSeuil.start()


                                }
                            }



                            Image {
                                id: sectionimg
                                width:111
                                source: "img/"+modelData+".png"
                                fillMode: Image.PreserveAspectFit
                                anchors.horizontalCenter: parent.horizontalCenter
                            }


                        }

                        Rectangle {
                            id: rectangle1
                            width: 130
                            height: 30
                            color: "#c2000000"
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter

                            Text {
                                id: _text
                                color: "#ffffff"
                                text: bdd.prenom[index]
                                font.letterSpacing: 0.3
                                font.pixelSize: 20
                                font.weight: Font.Black
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                        }





                    }
                }
            }
        }
    }

    Column {
        id: page2
        width: parent.width
        height: parent.height
        visible: false


        Rectangle {
            id: row
            width: parent.width
            height: parent.height/6
            color: "#0A1128"

            Image {
                id: imgRowPerso
                height: parent.height - parent.height / 10
                anchors.left: parent.left
                anchors.leftMargin: 25
                anchors.verticalCenter: parent.verticalCenter
                source: "img/PersoCatarina.png"
                fillMode: Image.PreserveAspectFit
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        imgRowPerso.source = "img/"+bdd.user.img+".png"
                        chartSeuil.theme = ChartView.ChartThemeBlueCerulean
                        percentChaude.color = "red"
                        percentFroide.color = "blue"
                        chartJourAndMois.theme = ChartView.ChartThemeBlueCerulean
                        barChaude.color = "red"
                        barFroide.color = "blue"
                        timerSeuil.stop()
                    }
                }


            }

            Label {
                id: label
                text: "Bonjour, Catarina"//qsTr("Bonjours, " + bdd.user.prenom)
                font.pointSize: 56
                anchors.centerIn: parent
                color: "#ffffff"
            }

            Image {
                id: name2
                height: parent.height
                anchors.right: parent.right
                source: "img/Deconnexion.png"
                fillMode: Image.PreserveAspectFit
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        page2.visible = false;
                        page1.visible = true;
                        serveur.closeElec();
                        timerSeuil.stop()
                    }
                }
            }
        }

        Rectangle{
            id: pageCharts
            width: parent.width
            height: parent.height - row.height
            color: "#EAF2E3"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#667eea"
                }

                GradientStop {
                    position: 1
                    color: "#764ba2"
                }
                orientation: Gradient.Vertical
            }

            Rectangle {
                id: rectangle_chartJourAndMois
                height: 470
                width: parent.width * 2/3
                color: "#00ffffff"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 0
                visible: true
                anchors.fill:undefined

                ChartView {
                    id:chartJourAndMois
                    anchors.fill: parent
                    title: "Consommation d'eau"
                    backgroundRoundness: 6
                    legend.alignment: Qt.AlignBottom
                    theme: ChartView.ChartThemeBlueCerulean
                    ValuesAxis{
                        id: valueaxis
                        min: 0
                        max: 100
                    }


                    BarSeries {
                        BarCategoryAxis {
                            id: axisXX
                            categories: ["1h-4h", "5h-8h", "9h-12h", "13h-16h", "17h-20h", "20h-24h"]
                            property bool mois: false
                        }
                        id: mySeries
                        axisX: axisXX
                        axisY: valueaxis
                        BarSet {
                            id: barChaude
                            label: "EauChaude"
                            values: [2, 2, 3, 4, 5, 6]
                            color: "red"
                            Component.onCompleted: {
                                // for(let i = 0; i < 6; i++){
                                //     console.log("lllaaaaaaaaaaaaa")
                                //     barbar.append(bdd.ec[i]);
                                // }


                            }
                        }

                        BarSet {
                            id: barFroide
                            label: "EauFroide"
                            values: [5, 1, 2, 4, 1, 7]
                            color: "blue"
                        }

                    }

                }

                RoundButton {
                    id: boutonChangeJourAndMois
                    width: 60
                    height: 60
                    radius: 40
                    text: "M/J"
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 3
                    anchors.bottomMargin: 2
                    display: AbstractButton.TextOnly
                    palette.button: hovered ? "#585858" : "black"
                    palette.buttonText: "white"
                    onClicked: {
                        if(axisXX.mois == false){
                            axisXX.categories = ["1J-5J", "6j-10j", "11j-15j", "16j-20j", "21j-25j", "26j-31j"]
                            console.log(axisXX.mois)
                            axisXX.mois = true
                            bdd.gestionCharts(false)
                            for(let i = 0; i < 6; i++){
                                barChaude.replace(i,bdd.ec[i]);
                                barFroide.replace(i,bdd.ef[i]);
                            }

                        }
                        else{
                            axisXX.categories =  ["1h-4h", "5h-8h", "9h-12h", "13h-16h", "17h-20h", "20h-24h"]
                            console.log("clik")
                            axisXX.mois = false
                            bdd.gestionCharts(true)
                            for(let i = 0; i < 6; i++){
                                barChaude.replace(i,bdd.ec[i]);
                                barFroide.replace(i,bdd.ef[i]);
                            }
                        }

                    }

                }


            }

            Rectangle {
                id: rectangle_chartSeuil
                width: 250
                height: parent.height - 30
                color: "#00ffffff"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 25
                ChartView {
                    id: chartSeuil
                    title: "Percent Bar Chart"
                    anchors.fill: parent
                    legend.alignment: Qt.AlignBottom
                    antialiasing: true
                    theme: ChartView.ChartThemeBlueCerulean




                    BarCategoryAxis{
                        id: ax
                        categories: ["A"]
                    }
                    ValuesAxis{
                        id: ay
                        min: 0
                        max: 100
                    }

                    BarSeries{
                        axisX: ax
                        axisY: ay
                        BarSet{
                            label: "EauChaude"
                            values: [0]
                            color: "red"
                            id: percentChaude
                        }
                        BarSet{
                            label: "EauFroide"
                            values: [30]
                            color: "blue"
                            id: percentFroide
                        }
                    }


                    LineSeries{
                        id: seuilSonor
                        axisX: ax
                        axisY: ay
                        color: "salmon"
                        width: 5

                        //XYPoint {x: -5; y: seuilSonor}
                        //XYPoint {x: 5; y: seuilSonor}
                    }

                    LineSeries{
                        id: seuilVisuel
                        axisX: ax
                        axisY: ay
                        color: "violet"
                        width: 5

                        //XYPoint {x: -5; y: seuilVisuel}
                        //XYPoint {x: 5; y: seuilVisuel}
                    }

                    LineSeries{
                        id: seuilCoupure
                        axisX: ax
                        axisY: ay
                        color: "orange"
                        width: 3.5

                        //XYPoint {x: -5; y: seuilSonor}
                        //XYPoint {x: 5; y: seuilSonor}
                    }

                    // BarCategoryAxis{
                    //     id: test
                    //     BarSet{
                    //         label: "valeurs"
                    //         values: [40, 75, 60]
                    //     }
                    // }
                    // CategoryAxis{
                    //     id:axys
                    //     //categoriesLabels: ["a", "b", "c"]
                    //     //orientation: Qt.Vertical
                    // }

                    // ValuesAxis{
                    //     id: axxs
                    //     min: 0
                    //     max: 100
                    // }

                    // LineSeries{
                    //     id: seuil1
                    //     axisX: axxs
                    //     axisY: axys
                    // }


                    // PercentBarSeries {
                    //     axisX: BarCategoryAxis { categories: ["2007"] }
                    //     BarSet { values: [2] }
                    // }
                    // LineSeries {
                    //         id: thresholdLine
                    //         color: "red"
                    //     }
                }

            }



        }
    }
    Timer{
        id: timerSeuil
        interval: 1000
        running: false
        repeat: true
        onTriggered: {
            if(percentChaude.at(0) >= seuilVisuel.at(0).y || percentFroide.at(0) >= seuilVisuel.at(0).y){
                imgRowPerso.source = "img/alarme.png"
                if(chartJourAndMois.theme == ChartView.ChartThemeBlueCerulean){
                    chartJourAndMois.theme = ChartView.ChartThemeHighContrast
                    chartSeuil.theme = ChartView.ChartThemeHighContrast
                    percentChaude.color = "red"
                    percentFroide.color = "blue"
                    barChaude.color = "red"
                    barFroide.color = "blue"
                    seuilVisuel.color = "violet"
                    seuilSonor.color = "salmon"
                    seuilCoupure.color= "orange"
                }
                else{
                    chartSeuil.theme = ChartView.ChartThemeBlueCerulean
                    percentChaude.color = "red"
                    percentFroide.color = "blue"
                    chartJourAndMois.theme = ChartView.ChartThemeBlueCerulean
                    barChaude.color = "red"
                    barFroide.color = "blue"
                    seuilVisuel.color = "violet"
                    seuilSonor.color = "salmon"
                    seuilCoupure.color= "orange"
                }
            }
        }
    }
}


/*##^##
Designer {
    D{i:0}D{i:1;invisible:true}
}
##^##*/
