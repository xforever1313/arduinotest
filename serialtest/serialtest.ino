const int BUFFER_SIZE = 100;
char buffer[BUFFER_SIZE + 1];
int bufferIndex;

String vers = "0.1.0";

enum Command
{
  SyntaxError = -1,
  Success = 0,
  Version = 1,
  Empty = 2
};

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

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
  for (int i = 0; i < bufferIndex; ++i)
  {
    if (buffer[i] >= 'a' && buffer[i] <= 'z')
    {
      buffer[i] -= 0x20;
    }
  }

  Serial.println("");
  WriteLine(buffer);
  bufferIndex = 0;
  buffer[0] = '\0';
  PrintPrompt();
}

void HandleCommand(Command command)
{
  Serial.println("");
  
  switch(command)
  {
    case Version:
      Serial.print("VERSION ");
      WriteLine(vers.c_str());
      break;

    case SyntaxError:
      WriteLine("ERROR: SYNTAX ERROR");
      break;

    case Empty:
      // No-Op.
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

