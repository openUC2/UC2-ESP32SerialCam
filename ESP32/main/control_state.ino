

static inline int8_t sgn(int val) {
  if (val < 0) return -1;
  if (val == 0) return 0;
  return 1;
}

// Custom function accessible by the API
void state_act_fct() {
  // here you can do something
  if (DEBUG) Serial.println("state_act_fct");

  // assign default values to thhe variables
  if (jsonDocument.containsKey("restart")) {
    ESP.restart();
  }


  jsonDocument.clear();
  jsonDocument["return"] = 1;
}

void state_set_fct() {
  // here you can set parameters

  int isdebug = jsonDocument["isdebug"];
  DEBUG = isdebug;
  jsonDocument.clear();
  jsonDocument["return"] = 1;

}

// Custom function accessible by the API
void state_get_fct() {
  // GET SOME PARAMETERS HERE
  if (jsonDocument.containsKey("isBusy")) {
    jsonDocument.clear();
    jsonDocument["isBusy"] = isBusy; // returns state of function that takes longer to finalize (e.g. motor)
  }
  else {
    jsonDocument.clear();
    jsonDocument["identifier_name"] = identifier_name;
    jsonDocument["identifier_id"] = identifier_id;
    jsonDocument["identifier_date"] = identifier_date;
    jsonDocument["identifier_author"] = identifier_author;
    jsonDocument["IDENTIFIER_NAME"] = IDENTIFIER_NAME;
  }
}

void printInfo() {
  if (DEBUG) Serial.println("You can use this software by sending JSON strings, A full documentation can be found here:");
  if (DEBUG) Serial.println("https://github.com/openUC2/UC2-REST/");
  //Serial.println("A first try can be: \{\"task\": \"/state_get\"");
}




bool isFirstRun() {
  // define preference name
  const char* prefName = "firstRun";
  preferences.begin(prefName, false);
  static const char dateKey[] = "date";
  const char *compiled_date = __DATE__ " " __TIME__;
  String stored_date = preferences.getString(dateKey, "");  // FIXME

  Serial.println("Stored date:");
  Serial.println(stored_date);
  Serial.println("Compiled date:");
  Serial.println(compiled_date);

  Serial.print("First run? ");
  if (!stored_date.equals(compiled_date)) {
    Serial.println("yes");
  } else {
    Serial.println("no");
  }

  preferences.putString(dateKey, compiled_date); // FIXME?
  preferences.end();
  return !stored_date.equals(compiled_date);
}
