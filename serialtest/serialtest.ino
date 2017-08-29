const int BUFFER_SIZE = 100;
char buffer[BUFFER_SIZE + 1];
int bufferIndex;

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
      processCommand();
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

void processCommand()
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

void WriteLine(char *ch)
{
  for (size_t i = 0; ch[i] != '\0'; ++i)
  {
    Serial.print(ch[i]);
  }
  Serial.println("");
}




