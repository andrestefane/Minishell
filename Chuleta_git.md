# 📝 Chuleta Git – Rama `andrei / alejandro`

Guía rápida para trabajar con Git 100% desde la terminal.

---

## 🚀 Flujo de trabajo diario

### 1. Empezar a trabajar en tu rama
```bash
git checkout andrei / alejandro          # Cambiar a tu rama
git pull origin andrei / alejandro       # Actualizar tu rama (por si acaso)
```

---

### 2. Subir cambios a tu rama
```bash
git add .                            # Añadir todos los archivos modificados
git commit -m "Descripcion clara del cambio"
git push origin andrei / alejandro              # Subir tu rama al repositorio
```

---

### 3. Actualizar main con tus cambios (merge)
```bash
git checkout main                   # Cambiar a la rama principal
git pull origin main                # Obtener últimos cambios de main
git merge andrei / alejandro                    # Unir tu trabajo desde la rama andrei
git push origin main                # Subir la rama main actualizada
```

---

## ✅ Recomendaciones
- Asegúrate de hacer `pull` antes de trabajar, para evitar conflictos.
- No olvides hacer `push` para subir tus cambios.
- Usa `git status` frecuentemente para ver en qué estado están tus archivos.
- Si hay conflictos durante el merge, Git te indicará qué archivos necesitan resolución.

---

Este archivo está pensado para ayudarte a ti y a tu equipo a mantener un flujo limpio y ordenado. ¡Happy coding! ✨

