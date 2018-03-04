//
//          Copyright Seth Hendrick 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

const int MIN_PIN_INDEX = 1;
const int MAX_PIN_INDEX = 13;

const int BUFFER_SIZE = 100;
char buffer[BUFFER_SIZE + 1];
int bufferIndex;

int state[MAX_PIN_INDEX - MIN_PIN_INDEX + 1];

String vers = "1.0.0";

enum Command
{
  SyntaxError = -1,
  Success = 0,
  Version = 1,
  Empty = 2,
  SetSuccess = 3,
  SetInvalidIndex = 4,
  SetNotANumber = 5,
  ClearSuccess = 6,
  ClearInvalidIndex = 7,
  ClearNotANumber = 8,
  GetState = 9,
  PrintHelp = 10,
  PrintAbout = 11,
  RespondToCanary = 12
};

void setup() {
  // put your setup code here, to run once:
  for (size_t i = MIN_PIN_INDEX; i <= MAX_PIN_INDEX; ++i)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    state[i-1] = LOW;
  }

  Serial.begin(115200);

  bufferIndex = 0;
  PrintPrompt();
}

void loop() {

  if (Serial.available() > 0)
  {
    char ch = Serial.read();

    if (ch != '\n' && ch != '\r')
    {
      buffer[bufferIndex++] = ch;

      // Echo back to terminal.
      Serial.write(ch);
    }
    
    if (ch == '\r')
    {
      buffer[bufferIndex] = '\0';
      Command cmd = ProcessCommand(buffer, bufferIndex);
      HandleCommand(cmd);
      bufferIndex = 0;
      buffer[0] = '\0';
    }
    else
    {
      if (bufferIndex == BUFFER_SIZE)
      {
        BufferFull();
      }
    }
  }
}

void EchoSuccess()
{
  String str(buffer);
  str.toUpperCase();
  WriteLine(str.c_str());
}

void HandleCommand(Command command)
{
  Serial.println("");
  
  switch(command)
  {
    case SyntaxError:
      WriteLine("ERROR: SYNTAX ERROR");
      break;

    case Empty:
      // No-Op.
      break;
    
    case Version:
      Serial.print("VERSION ");
      WriteLine(vers.c_str());
      break;

    case SetSuccess:
      EchoSuccess();
      break;

    case ClearSuccess:
      EchoSuccess();
      break;

    case SetInvalidIndex:
    case ClearInvalidIndex:
      WriteLine("ERROR: INDEX OUT OF RANGE");
      break;

    case SetNotANumber:
    case ClearNotANumber:
      WriteLine("ERROR: NOT A POSTIVE NONZERO INTEGER");
      break;

    case GetState:
      PrintState();
      break;

    case PrintHelp:
      PrintHelpInfo();
      break;

    case PrintAbout:
      PrintAboutInfo();
      break;

    case RespondToCanary:
      WriteLine("I'M DOING SCIENCE AND I'M STILL ALIVE!");
      break;

    default:
      WriteLine("ERROR: UNKNOWN COMMAND");
  }

  PrintPrompt();
}

void BufferFull()
{
  Serial.println("");
  Serial.println("ERROR: BUFFER FULL, DUMPING BUFFER");
  bufferIndex=0;
  PrintPrompt();
}

void PrintPrompt()
{
  Serial.print("# ");
}

void WriteLine(const char *ch)
{
  for (size_t i = 0; ch[i] != '\0'; ++i)
  {
    Serial.print(ch[i]);
  }
  Serial.println("");
}

void PrintAboutInfo()
{
  WriteLine("Arduino serial pin setter");
  WriteLine("Created By Seth Hendrick");
  WriteLine("https://github.com/xforever1313/arduinotest/tree/master/SerialPinSetter");
  WriteLine("Released under the BOOST SOFTWARE LICENSE V1.0");
  WriteLine("END-OF-LIST");
}

void PrintHelpInfo()
{
  WriteLine("version\t-Print firmware version");
  WriteLine("help\t-Prints this list");
  WriteLine("about\t-About the firmware");
  WriteLine("state\t-Get what the pins are currently set to");
  WriteLine("set x\t-Set pin x to HIGH, where 1 <= x <= 13");
  WriteLine("clear x\t-Clear pin x to LOW, where 1 <= x <= 13");
  WriteLine("canary\t-Send this command to see if I am alive without changing state");
  WriteLine("END-OF-LIST");
}

void PrintState()
{
  // This sizeof only works because its not on the heap.
  size_t arraySize = sizeof(state)/sizeof(int);
  for (size_t i = 0; i < arraySize; ++i)
  {
    Serial.print("Pin ");
    Serial.print(i + 1);
    Serial.print(" - ");
    Serial.println(state[i]);
  }
  WriteLine("END-OF-LIST");
}

