char *str_tolower (const char *ct)
{
  char *s = NULL;

  if (ct != NULL)
  {
    int i;

    s = malloc (sizeof (*s) * (strlen (ct) + 1));
    if (s != NULL)
    {
      for (i = 0; ct[i]; i++)
      {
        s[i] = tolower (ct[i]);
      }
      s[i] = '\0';
    }
  }
  return s;
}

char *str_toupper (const char *ct)
{
  char *s = NULL;

  if (ct != NULL)
  {
    int i;

    s = malloc (sizeof (*s) * (strlen (ct) + 1));
    if (s != NULL)
    {
      for (i = 0; ct[i]; i++)
      {
        s[i] = toupper (ct[i]);
      }
      s[i] = '\0';
    }
  }
  return s;
}

int str_istr (const char *cs, const char *ct)
{
  int index = -1;

  if (cs != NULL && ct != NULL)
  {
    char *ptr_pos = NULL;

    ptr_pos = strstr (cs, ct);
    if (ptr_pos != NULL)
    {
      index = ptr_pos - cs;
    }
  }
  return index;
}

char *str_sub (const char *s, unsigned int start, unsigned int end)
{
  char *new_s = NULL;

  if (s != NULL && start < end)
  {
    new_s = malloc (sizeof (*new_s) * (end - start + 2));
    if (new_s != NULL)
    {
      int i;

      for (i = start; i <= end; i++)
      {
        new_s[i-start] = s[i];
      }
      new_s[i-start] = '\0';
    }
    else
    {
      fprintf (stderr, "Memoire insuffisante\n");
      exit (EXIT_FAILURE);
    }
  }
  return new_s;
}

char **str_split (char *s, const char *ct)
{
  char **tab = NULL;

  if (s != NULL && ct != NULL)
  {
    int i;
    char *cs = NULL;
    size_t size = 1;

    for (i = 0; (cs = strtok (s, ct)); i++)
    {
      if (size <= i + 1)
      {
        void *tmp = NULL;

        size <<= 1;
        tmp = realloc (tab, sizeof (*tab) * size);
        if (tmp != NULL)
        {
          tab = tmp;
        }
        else
        {
          fprintf (stderr, "Memoire insuffisante\n");
          free (tab);
          tab = NULL;
          exit (EXIT_FAILURE);
        }
      }
      tab[i] = cs;
      s = NULL;
    }
    tab[i] = NULL;
  }
  return tab;
}

char *str_join (char *cs, ...)
{
  va_list va;
  const char *ct;
  char *s = NULL;
  size_t size = 0;

  va_start (va, cs);
  while ((ct = va_arg (va, char *)) != NULL)
  {
    void *tmp = NULL;

    size += strlen (ct) + strlen (cs);
    tmp = realloc (s, sizeof (*s) * (size + 1));
    if (tmp != NULL)
    {
      if (s == NULL)
      {
        s = tmp;
        strcpy (s, ct);
      }
      else
      {
         s = tmp;
         strcat (s, cs);
         strcat (s, ct);
      }
    }
    else
    {
      fprintf (stderr, "Memoire insuffisante\n");
      free (s);
      s = NULL;
      exit (EXIT_FAILURE);
    }
  }
  return s;
}

char *str_remplace (const char *s, unsigned int start, unsigned int lenght, const char *ct)
{
  char *new_s = NULL;

  if (s != NULL && ct != NULL && start >= 0 && lenght > 0)
  {
    size_t size = strlen (s);

    new_s = malloc (sizeof (*new_s) * (size - lenght + strlen (ct) + 1));
    if (new_s != NULL)
    {
      memcpy (new_s, s, start);
      memcpy (&new_s[start], ct, strlen (ct));
      memcpy (&new_s[start + strlen (ct)], &s[start + lenght], size - lenght - start + 1);
    }
  }
  else
  {
    fprintf (stderr, "Memoire insuffisante\n");
    exit (EXIT_FAILURE);
  }
  return new_s;
}

char *str_strip (const char *string)
{
  char *strip = NULL;

  if (string != NULL)
  {
    strip = malloc (sizeof (*strip) * (strlen (string) + 1));
    if (strip != NULL)
    {
      int i, j;
      int ps = 0;

      for (i = 0, j = 0; string[i]; i++)
      {
        if (string[i] == ' ')
        {
          if (ps == 0)
          {
            strip[j] = string[i];
            ps = 1;
            j++;
          }
        }
        else
        {
          strip[j] = string[i];
          ps = 0;
          j++;
        }
      }
      strng[j] = '\0';
    }
    else
    {
      fprintf (stderr, "Memoire insuffisante\n");
      exit (EXIT_FAILURE);
    }
  }
  return strip;
}