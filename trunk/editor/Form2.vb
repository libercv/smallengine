Public Class Form2
    Private WithEvents view As GLView

    Public Sub New()
        ' Llamada necesaria para el Dise�ador de Windows Forms.
        InitializeComponent()

        view = New GLView
        view.Parent = Me
        view.Dock = DockStyle.Fill
        Me.Controls.Add(view)

        ' Agregue cualquier inicializaci�n despu�s de la llamada a InitializeComponent().
    End Sub

    Private Sub view_Paint(ByVal sender As Object, ByVal e As System.Windows.Forms.PaintEventArgs) Handles view.Paint
    End Sub
End Class