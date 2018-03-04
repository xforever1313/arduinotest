
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
      return SetNotANumber;
    }
    else if ((index < MIN_PIN_INDEX) || (index > MAX_PIN_INDEX))
    {
      return SetInvalidIndex;
    }
    else
    {
      digitalWrite(index, HIGH);
      state[index-1] = HIGH;
      return SetSuccess;
    }
  }
  else if (s.startsWith("clear"))
  {
    String indexStr = s.substring(5);
    int index = indexStr.toInt();
    if (index <= 0)
    {
      return ClearNotANumber;
    }
    else if ((index < MIN_PIN_INDEX) || (index > MAX_PIN_INDEX))
    {
      return ClearInvalidIndex;
    }
    else
    {
      digitalWrite(index, LOW);
      state[index-1] = LOW;
      return ClearSuccess;
    }
  }
  else if (s.equals("?") || s.equals("help"))
  {
    return PrintHelp;
  }
  else if (s.equals("state"))
  {
    return GetState;
  }
  else if(s.equals("about"))
  {
    return PrintAbout;
  }
  else if (s.equals("canary"))
  {
    return RespondToCanary;
  }
  
  return SyntaxError;
}

