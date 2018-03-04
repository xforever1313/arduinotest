
Command ProcessCommand(const char* str, int strLen)
{
  String s(str);
  s.toLowerCase();
  if (strLen == 0)
  {
    return Empty;
  }
  else if (s.equals("vers") || s.equals("version"))
  {
    return Version;
  }
  else if (s.startsWith("set"))
  {
    String indexStr = s.substring(3);
    int index = indexStr.toInt();
    if (index <= 0)
    {
      return SyntaxError;
    }
    else if ((index < MIN_PIN_INDEX) || (index > MAX_PIN_INDEX))
    {
      return SetInvalidIndex;
    }
    else
    {
      digitalWrite(index, HIGH);
      return SetSuccess;
    }
  }
  else if (s.startsWith("clear"))
  {
    String indexStr = s.substring(5);
    int index = indexStr.toInt();
    if (index <= 0)
    {
      return SyntaxError;
    }
    else if ((index < MIN_PIN_INDEX) || (index > MAX_PIN_INDEX))
    {
      return ClearInvalidIndex;
    }
    else
    {
      digitalWrite(index, LOW);
      return ClearSuccess;
    }
  }
  
  return SyntaxError;
}

