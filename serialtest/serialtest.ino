const int MIN_PIN_INDEX = 1;
const int MAX_PIN_INDEX = 13;

const int BUFFER_SIZE = 100;
char buffer[BUFFER_SIZE + 1];
int bufferIndex;

String vers = "0.1.0";

enum Command
{
  SyntaxError = -1,
  Success = 0,
  Version = 1,
  Empty = 2,
  SetSuccess = 3,
  SetInvalidIndex = 4,
  ClearSuccess = 5,
  ClearInvalidIndex = 6
};

void setup() {
  // put your setup code here, to run once:
  for (int i = MIN_PIN_INDEX; i <= MAX_PIN_INDEX; ++i)
  {
    pinMode(i, OUTPUT);
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

  // put your main code here, to run repeatedly:
  //digitalWrite(4, HIGH);
  //delay(1000);
  //digitalWrite(4, LOW);
  //delay(1000);
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
      WriteLine("ERROR: Index out of range");
      break;

    case ClearInvalidIndex:
      WriteLine("ERROR: Index out of range");
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

