eprecated\" auf FALSE festgelegt ist."
							}
						},
						"additionalProperties": false
					},
					"debug": {
						"type": "object",
						"description": "Ein optionales Objekt, das Debugoptionen angibt.",
						"properties": {
							"output": {
								"type": "boolean",
								"description": "Ein optionaler boolescher Wert. Eine Festlegung auf TRUE entspricht der Übergabe von \"--debug-output\" in der Befehlszeile."
							},
							"tryCompile": {
								"type": "boolean",
								"description": "Ein optionaler boolescher Wert. Eine Festlegung auf TRUE entspricht der Übergabe von \"--debug-trycompile\" in der Befehlszeile."
							},
							"find": {
								"type": "boolean",
								"description": "Ein optionaler boolescher Wert. Eine Festlegung auf TRUE entspricht der Übergabe von --debug-find\" in der Befehlszeile."
							}
						},
						"additionalProperties": false
					},
					"installDir": {
						"type": "string",
						"description": "Eine optionale Zeichenfolge, die den Pfad zum Installationsverzeichnis darstellt. Dieses Feld unterstützt die Makroerweiterung. Wenn ein relativer Pfad angegeben ist, wird er relativ zum Quellverzeichnis berechnet."
					},
					"toolchainFile": {
						"type": "string",
						"description": "Eine optionale Zeichenfolge, die den Pfad zur Toolchain-Datei darstellt. Dieses Feld unterstützt die Makroerwe