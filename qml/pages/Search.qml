import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: root

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        VerticalScrollDecorator {}

        Column {
            id: column
            width: parent.width

            PageHeader { title: qsTr("Search") }

            Column {
                width: parent.width
                spacing: -Theme.paddingSmall

                Button {
                    id: wizard

                    property string location
                    property string selection

                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Setup parameters")
                    onClicked: pageStack.animatorPush(locationWizardPage)
                }

                SectionHeader {
                    x: Theme.horizontalPageMargin
                    text: qsTr("Location")
                }

                Label{
                    x: Theme.horizontalPageMargin
                    text: wizard.location
                    color: Theme.highlightColor
                }

                SectionHeader {
                    x: Theme.horizontalPageMargin
                    text: qsTr("Selection")
                }

                Label{
                    x: Theme.horizontalPageMargin
                    text: wizard.selection
                    color: Theme.highlightColor
                }

                Component {
                    id: locationWizardPage

                    Dialog {
                        id: locationWizardWizard

                        property string searchString
                        property int location: 0

                        canAccept: location > 0
                        acceptDestination: datesWizardPage

                        onAcceptPendingChanged: {
                            if (acceptPending) {
                                // Tell the destination page what the selected category is
                                acceptDestinationInstance.category = 'Fruit'
                            }
                        }

                        onSearchStringChanged: locationModel.update(searchString)

                        Text {
                            visible: locationModel.networkError !== ""
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottomMargin: Theme.paddingLarge
                            width: parent.width - 2 * Theme.horizontalPageMargin
                            x: Theme.horizontalPageMargin
                            anchors.centerIn: parent
                            text: locationModel.networkError
                            color: Theme.errorColor
                            font.pixelSize: Theme.fontSizeSmall
                            wrapMode: Text.WrapAnywhere
                        }

                        SilicaListView {
                            model: locationModel
                            anchors.fill: parent
                            currentIndex: -1 // otherwise currentItem will steal focus
                            header:  SearchField {
                                id: locationSearchField
                                width: parent.width

                                Binding {
                                    target: locationWizardWizard
                                    property: "searchString"
                                    value: locationSearchField.text.toLowerCase().trim()
                                }
                            }

                            delegate: BackgroundItem {
                                id: backgroundItem

                                ListView.onAdd: AddAnimation {
                                    target: backgroundItem
                                }
                                ListView.onRemove: RemoveAnimation {
                                    target: backgroundItem
                                }

                                onClicked: locationWizardWizard.location=1

                                Label {
                                    x: Theme.horizontalPageMargin
                                    anchors.verticalCenter: parent.verticalCenter
                                    color: searchString.length > 0 ? (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
                                                                   : (highlighted ? Theme.highlightColor : Theme.primaryColor)
                                    textFormat: Text.StyledText
                                    text: Theme.highlightText(model.name, searchString, Theme.highlightColor) + ' [' + model.id + ']'
                                }
                            }

                            VerticalScrollDecorator {}

                        }

                        ListModel {
                            id: listModel

                            // copied under creative commons license from Wikipedia
                            // http://en.wikipedia.org/wiki/List_of_sovereign_states
                            property var countries: ["Afghanistan", "Albania", "Algeria", "Andorra", "Angola",
                                "Antigua and Barbuda", "Argentina", "Armenia", "Australia", "Austria",
                                "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados",
                                "Belarus", "Belgium", "Belize", "Benin", "Bhutan",
                                "Bolivia", "Bosnia and Herzegovina", "Botswana", "Brazil", "Brunei",
                                "Bulgaria", "Burkina Faso", "Burma", "Burundi", "Cambodia",
                                "Cameroon", "Canada", "Cape Verde", "Central African Republic", "Chad",
                                "Chile", "China", "Colombia", "Comoros", "Costa Rica",
                                "Croatia", "Cuba", "Cyprus", "Czech Republic", "Denmark",
                                "Djibouti", "Dominica", "Dominican Republic", "East Timor", "Ecuador",
                                "Egypt", "El Salvador", "Equatorial Guinea", "Eritrea", "Estonia",
                                "Ethiopia", "Fiji", "Finland", "France", "Gabon",
                                "Gambia", "Georgia", "Germany", "Ghana", "Greece",
                                "Grenada", "Guatemala", "Guinea", "Guinea-Bissau", "Guyana",
                                "Haiti", "Honduras", "Hungary", "Iceland", "India",
                                "Indonesia", "Iran", "Iraq", "Ireland", "Israel",
                                "Italy", "Jamaica", "Japan", "Jordan", "Kazakhstan",
                                "Kenya", "Kiribati", "Korea North", "Korea South", "Kuwait",
                                "Kyrgyzstan", "Laos", "Latvia", "Lebanon", "Lesotho",
                                "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg",
                                "Macedonia", "Madagascar", "Malawi", "Malaysia", "Maldives",
                                "Mali", "Malta", "Marshall Islands", "Mauritania", "Mauritius",
                                "Mexico", "Micronesia", "Moldova", "Monaco", "Mongolia",
                                "Montenegro", "Morocco", "Mozambique", "Namibia", "Nauru",
                                "Nepal", "Netherlands", "New Zealand", "Nicaragua", "Niger",
                                "Nigeria", "Norway", "Oman", "Pakistan", "Palau",
                                "Panama", "Papua New Guinea", "Paraguay", "Peru", "Philippines",
                                "Poland", "Portugal", "Qatar", "Romania", "Russia",
                                "Rwanda", "Saint Kitts and Nevis", "Saint Lucia", "Saint Vincent and the Grenadines", "Samoa",
                                "San Marino", "Saudi Arabia", "Senegal", "Serbia", "Seychelles",
                                "Sierra Leone", "Singapore", "Slovakia", "Slovenia", "Solomon Islands",
                                "Somalia", "South Africa", "South Sudan", "Spain", "Sri Lanka",
                                "Sudan", "Suriname", "Swaziland", "Sweden", "Switzerland",
                                "Syria", "Tajikistan", "Tanzania", "Thailand", "Togo",
                                "Tonga", "Trinidad and Tobago", "Tunisia", "Turkey", "Turkmenistan",
                                "Tuvalu", "Uganda", "Ukraine", "United Arab Emirates", "United Kingdom",
                                "United States", "Uruguay", "Uzbekistan", "Vanuatu", "Vatican City",
                                "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe",
                                "Abkhazia", "Cook Islands", "Kosovo", "Nagorno-Karabakh", "Niue",
                                "Northern Cyprus", "Palestine", "SADR", "Somaliland", "South Ossetia",
                                "Taiwan"]

                            function update() {
                                var filteredCountries = countries.filter(function (country) { return country.toLowerCase().indexOf(searchString) !== -1 })

                                var country
                                var found
                                var i

                                // helper objects that can be quickly accessed
                                var filteredCountryObject = new Object
                                for (i = 0; i < filteredCountries.length; ++i) {
                                    filteredCountryObject[filteredCountries[i]] = true
                                }
                                var existingCountryObject = new Object
                                for (i = 0; i < count; ++i) {
                                    country = get(i).text
                                    existingCountryObject[country] = true
                                }

                                // remove items no longer in filtered set
                                i = 0
                                while (i < count) {
                                    country = get(i).text
                                    found = filteredCountryObject.hasOwnProperty(country)
                                    if (!found) {
                                        remove(i)
                                    } else {
                                        i++
                                    }
                                }

                                // add new items
                                for (i = 0; i < filteredCountries.length; ++i) {
                                    country = filteredCountries[i]
                                    found = existingCountryObject.hasOwnProperty(country)
                                    if (!found) {
                                        // for simplicity, just adding to end instead of corresponding position in original list
                                        append({ "text": country})
                                    }
                                }
                            }
                        }

                    }

                }

                Component {
                    id: datesWizardPage

                    Dialog {
                        canAccept: selector.currentIndex >= 0
                        acceptDestination: root
                        acceptDestinationAction: PageStackAction.Pop

                        property string category

                        ListModel {
                            id: fruitModel
                            ListElement {
                                name: 'Apple'
                            }
                            ListElement {
                                name: 'Banana'
                            }
                            ListElement {
                                name: 'Cantaloupe'
                            }
                        }

                        ListModel {
                            id: vegetableModel
                            ListElement {
                                name: 'Asparagus'
                            }
                            ListElement {
                                name: 'Broccoli'
                            }
                            ListElement {
                                name: 'Carrot'
                            }
                        }

                        Flickable {
                            // ComboBox requires a flickable ancestor
                            width: parent.width
                            height: parent.height
                            interactive: false

                            Column {
                                width: parent.width

                                DialogHeader {
                                    title: "Select " + category.toLowerCase()
                                }

                                ComboBox {
                                    id: selector

                                    width: parent.width
                                    label: 'Selection:'
                                    currentIndex: -1

                                    menu: ContextMenu {
                                        Repeater {
                                            model: category === 'Fruit' ? fruitModel : vegetableModel

                                            MenuItem {
                                                text: modelData
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        onAccepted: {
                            wizard.selection = selector.value
                        }
                    }
                }
            }

        }

    }

}
